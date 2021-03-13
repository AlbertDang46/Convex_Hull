#ifndef CHANSALGORITHM_H
#define CHANSALGORITHM_H

#include <vector>
#include <cmath>
#include "Point.h"
#include "GrahamScan.h"

using namespace std;

vector<point> ChansAlgorithm(const vector<point>& p) {
    point pointOnHull = getLowestLeftmostPoint(p);
    point prevPointOnHull(pointOnHull.x - 1, pointOnHull.y);

    for (int t = 1; t < log2(log2(p.size())); t++) {
        vector<point> hull;
        int m = (int) pow(2, pow(2, t));

        vector<vector<point>> subSets;
        vector<point> temp;
        for (int i = 0; i < p.size(); i++) {
            temp.push_back(p[i]);

            if (temp.size() == m) {
                subSets.push_back(temp);
                temp.clear();
            }
        }

        if (!temp.empty())
            subSets.push_back(temp);

        vector<vector<point>> subSetHulls;
        for (int i = 0; i < subSets.size(); i++)
            subSetHulls.push_back(GrahamScan(subSets[i]));

        for (int i = 0; i < m; i++) {
            hull.push_back(pointOnHull);
            
            vector<point> tangentPoints;
            for (int j = 0; j < subSetHulls.size(); j++) {
                pair<point, point> tangents = tangentPointPolygon(pointOnHull, subSetHulls[j]); 
                tangentPoints.push_back(tangents.first);
                tangentPoints.push_back(tangents.second);
            }
            
            point endPoint = tangentPoints[0];
            double angle = 0.0;

            for (int j = 0; j < tangentPoints.size(); j++) {
                double newAngle = getAngle(prevPointOnHull, pointOnHull, tangentPoints[j]);
                if ((newAngle > angle) || 
                    (fabs(newAngle - angle) <= numeric_limits<double>::epsilon() && 
                    getDistance(pointOnHull, tangentPoints[i]) > getDistance(pointOnHull, endPoint))) {

                    angle = newAngle;
                    endPoint = tangentPoints[j];
                }
            }

            prevPointOnHull = pointOnHull;
            pointOnHull = endPoint;

            if (pointOnHull == hull[0])
                return hull;
        }
    }

    return vector<point>(0);
}

#endif