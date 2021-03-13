#ifndef POINT_H
#define POINT_H

#include <vector>
#include <utility>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

struct point {
    int x;
    int y;

    point() : x(0), y(0) {}
    point(int x_, int y_) : x(x_), y(y_) {}

    bool operator==(const point& p) const {
        return x == p.x && y == p.y;
    }

    bool operator!=(const point& p) const {
        return x != p.x || y != p.y;
    }

    bool operator<(const point& p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

double getDistance(point a, point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double getAngle(point a, point b, point c) {
    if (b == c)
        return 0.0;

    double lengthAB = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    double lengthBC = sqrt(pow(b.x - c.x, 2) + pow(b.y - c.y, 2));
    double lengthCA = sqrt(pow(c.x - a.x, 2) + pow(c.y - a.y, 2));

    double angle = acos((pow(lengthBC, 2) + pow(lengthAB, 2) - pow(lengthCA, 2)) / (2 * lengthBC * lengthAB));

    return angle;
}

int getOrientation(point p1, point p2, point p3) 
{ 
    int val = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y); 
  
    if (val == 0) 
        return 0;
  
    return (val > 0) ? 1 : 2;
}

double distancePointtoLine(point a, point b, point p) {
    double slope = (a.y - b.y) / (a.x - b.x);
    double intercept = a.y - (slope * a.x);

    double distance = fabs((slope * p.x) + (-1 * p.y) + intercept) / sqrt(pow(slope, 2) + pow(-1, 2));

    return distance;
}

point getLeftmostLowestPoint(const vector<point>& p) {
    point leftmost = p[0];

    for (int i = 0; i < p.size(); i++) {
        if (p[i].x < leftmost.x || (p[i].x == leftmost.x && p[i].y < leftmost.y))
            leftmost = p[i];
    }

    return leftmost;
}

point getRightmostHighestPoint(const vector<point>& p) {
    point rightmost = p[0];

    for (int i = 0; i < p.size(); i++) {
        if (p[i].x > rightmost.x || (p[i].x == rightmost.x && p[i].y > rightmost.y))
            rightmost = p[i];
    }

    return rightmost;
}

point getLowestLeftmostPoint(const vector<point>& p) {
    point lowest = p[0];

    for (int i = 0; i < p.size(); i++) {
        if (p[i].y < lowest.y || (p[i].y == lowest.y && p[i].x < lowest.x))
            lowest = p[i];
    }

    return lowest;
}

vector<point> removeDuplicateAngles(const vector<point>& p, point lowest, point lowestXAxis) {
    vector<point> result;
    point check(-1, -1);

    for (int i = 0; i < p.size(); i++) {
        double checkAngle = getAngle(lowestXAxis, lowest, check);
        double curAngle = getAngle(lowestXAxis, lowest, p[i]);
        double checkDistance = getDistance(lowest, check);
        double curDistance = getDistance(lowest, p[i]);
        
        if (fabs(checkAngle - curAngle) <= numeric_limits<double>::epsilon()) {
            if (curDistance > checkDistance)
                result.pop_back();
            else
                continue;
        }

        result.push_back(p[i]);
        check = p[i];
    }

    return result;
}

point getFarthestFromLine(const vector<point>& p, point a, point b) {
    point farthest = p[0];
    double distance = 0.0;

    for (int i = 0; i < p.size(); i++) {
        double newDistance = distancePointtoLine(a, b, p[i]);
        if (newDistance > distance) {
            distance = newDistance;
            farthest = p[i]; 
        }
    }

    return farthest;
}

bool aboveLine(point p1, point p2, point p3) {
    if (getOrientation(p1, p2, p3) == 2)
        return true;

    return false;
}

bool belowLine(point p1, point p2, point p3) {
    if (getOrientation(p1, p2, p3) == 1)
        return true;

    return false;
}

point leftTangentPointPolygon(point p, int n, const vector<point>& polygon) {
    int a, b, c;
    int dnA, dnC;

    if (aboveLine(p, polygon[n-1], polygon[0]) && !belowLine(p, polygon[1], polygon[0]))
        return polygon[0];

    for (a = 0, b = n;;) {
        c = (a + b) / 2;
        dnC = belowLine(p, polygon[c+1], polygon[c]);
        if (aboveLine(p, polygon[c-1], polygon[c]) && !dnC)
            return polygon[c];

        dnA = belowLine(p, polygon[a+1], polygon[a]);
        if (dnA) {
            if (!dnC) {
                b = c;
            } else {
                if (belowLine(p, polygon[a], polygon[c]))
                    b = c;
                else
                    a = c;
            }
        } else {
            if (dnC) {
                a = c;
            } else {
                if (aboveLine(p, polygon[a], polygon[c]))
                    b = c;
                else
                    a = c;
            }
        }
    }
}

point rightTangentPointPolygon(point p, int n, const vector<point>& polygon) {
    int a, b, c;
    int upA, dnC;

    if (belowLine(p, polygon[1], polygon[0]) && !aboveLine(p, polygon[n-1], polygon[0]))
        return polygon[0];

    for (a = 0, b = n;;) {
        c = (a + b) / 2;
        dnC = belowLine(p, polygon[c+1], polygon[c]);
        if (dnC && !aboveLine(p, polygon[c-1], polygon[c]))
            return polygon[c];

        upA = aboveLine(p, polygon[a+1], polygon[a]);
        if (upA) {
            if (dnC) {
                b = c;
            } else {
                if (aboveLine(p, polygon[a], polygon[c]))
                    b = c;
                else
                    a = c;
            }
        } else {
            if (!dnC) {
                a = c;
            } else {
                if (belowLine(p, polygon[a], polygon[c]))
                    b = c;
                else
                    a = c;
            }
        }
    }
}

pair<point, point> tangentPointPolygon(point p, const vector<point>& polygon) {
    vector<point> newPolygon = polygon;
    newPolygon.push_back(polygon.front());

    return pair<point, point>(leftTangentPointPolygon(p, polygon.size(), newPolygon), rightTangentPointPolygon(p, polygon.size(), newPolygon));
}

bool onSegment(point p, point q, point r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;

    return false;
}

bool doIntersect(point p1, point q1, point p2, point q2) {
    int o1 = getOrientation(p1, q1, p2);
    int o2 = getOrientation(p1, q1, q2);
    int o3 = getOrientation(p2, q2, p1);
    int o4 = getOrientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

bool isInsidePolygon(point p, const vector<point>& polygon) {
    if (polygon.size() < 3)
        return false;

    point extreme(INT_MAX, p.y);

    int count = 0, i = 0;

    do {
        int next = (i+1) % polygon.size();

        if (doIntersect(polygon[i], polygon[next], p, extreme)) {
            if (getOrientation(polygon[i], p, polygon[next]) == 0)
                return onSegment(polygon[i], p, polygon[next]);

            count++;
        }

        i = next;
    } while (i != 0);

    return count & 1;
}

vector<point> removeNonConvexHullPointsQuad(const vector<point>& p) {
    vector<point> potentialHullPoints;

    vector<point> quad(4, p[0]);
    for (int i = 0; i < p.size(); i++) {
        if (p[i].x < quad[0].x)
            quad[0] = p[i];

        if (p[i].y < quad[1].y)
            quad[1] = p[i];

        if (p[i].x > quad[2].x)
            quad[2] = p[i];

        if (p[i].y > quad[3].y)
            quad[3] = p[i];
    }

    for (int i = 0; i < p.size(); i++) {
        if (!isInsidePolygon(p[i], quad))
            potentialHullPoints.push_back(p[i]);
    }

    return potentialHullPoints;
}

vector<point> removeNonConvexHullPointsOctagon(const vector<point>& p) {
    vector<point> potentialHullPoints;

    vector<point> octagon(8, p[0]);
    for (int i = 0; i < p.size(); i++) {
        if (p[i].x < octagon[0].x)
            octagon[0] = p[i];

        if (p[i].x + p[i].y < octagon[1].x + octagon[1].y)
            octagon[1] = p[i];

        if (p[i].y < octagon[2].y)
            octagon[2] = p[i];

        if (p[i].x - p[i].y > octagon[3].x - octagon[3].y)
            octagon[3] = p[i];

        if (p[i].x > octagon[4].x)
            octagon[4] = p[i];

        if (p[i].x + p[i].y > octagon[5].x + octagon[5].y)
            octagon[5] = p[i];

        if (p[i].y > octagon[6].y)
            octagon[6] = p[i];

        if (p[i].x - p[i].y < octagon[7].x - octagon[7].y)
            octagon[7] = p[i];
    }

    for (int i = 0; i < p.size(); i++) {
        if (!isInsidePolygon(p[i], octagon))
            potentialHullPoints.push_back(p[i]);
    }

    return potentialHullPoints;
}

#endif