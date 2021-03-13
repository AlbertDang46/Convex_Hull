#ifndef GRAHAMSCAN_H
#define GRAHAMSCAN_H

#include <vector>
#include <algorithm>
#include "Point.h"

using namespace std;

vector<point> GrahamScan(const vector<point>& p) {
    vector<point> points = p;
    vector<point> hull;

    point lowest = getLowestLeftmostPoint(p);
    point lowestXAxis(lowest.x + 1, lowest.y);
    sort(points.begin(), points.end(), [lowest, lowestXAxis] (const point& lhs, const point& rhs) -> bool { return getAngle(lowestXAxis, lowest, lhs) < getAngle(lowestXAxis, lowest, rhs); });
    points = removeDuplicateAngles(points, lowest, lowestXAxis);

    for (int i = 0; i < points.size(); i++) {
        while (hull.size() > 1 && getOrientation(hull[hull.size() - 2], hull.back(), points[i]) <= 1)
            hull.pop_back();

        hull.push_back(p[i]);
    }

    return hull;
}

#endif