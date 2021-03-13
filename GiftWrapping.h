#ifndef GIFTWRAPPING_H
#define GIFTWRAPPING_H

#include <vector>
#include "Point.h"

using namespace std;

vector<point> GiftWrapping(const vector<point>& p) {
    vector<point> hull;
    
    point pointOnHull = getLeftmostLowestPoint(p);
    point prevPointOnHull(pointOnHull.x, pointOnHull.y - 1);

    do {
        hull.push_back(pointOnHull);

        point endPoint = p[0];
        double angle = 0.0;

        for (int i = 0; i < p.size(); i++) {
            double newAngle = getAngle(prevPointOnHull, pointOnHull, p[i]);
            if ((newAngle > angle) || 
                (fabs(newAngle - angle) <= numeric_limits<double>::epsilon() && 
                 getDistance(pointOnHull, p[i]) > getDistance(pointOnHull, endPoint))) {

                angle = newAngle;
                endPoint = p[i];
            }
        }

        prevPointOnHull = pointOnHull;
        pointOnHull = endPoint;
    } while (pointOnHull != hull[0]);

    return hull;
}

#endif