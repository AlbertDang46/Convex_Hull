#ifndef QUICKHULL_H
#define QUICKHULL_H

#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <vector>
#include "Point.h"

using namespace std;

vector<point> FindHull(const vector<point>& p, point leftmost, point rightmost) {
    if (p.empty())
        return vector<point>(0);

    point farthest = getFarthestFromLine(p, leftmost, rightmost);

    vector<point> leftSide;
    vector<point> rightSide;

    for (int i = 0; i < p.size(); i++) {
        if (getOrientation(rightmost, farthest, p[i]) == 1)
            rightSide.push_back(p[i]);
        else if (getOrientation(leftmost, farthest, p[i]) == 2)
            leftSide.push_back(p[i]);
    }

    vector<point> leftHull = FindHull(leftSide, leftmost, farthest);
    vector<point> rightHull = FindHull(rightSide, farthest, rightmost);

    vector<point> hull;
    for (int i = 0; i < leftHull.size(); i++)
        hull.push_back(leftHull[i]);

    hull.push_back(farthest);

    for (int i = 0; i < rightHull.size(); i++)
        hull.push_back(rightHull[i]);    

    return hull;
}

vector<point> QuickHull(const vector<point>& p) {
    vector<point> hull;

    point leftmost = getLeftmostLowestPoint(p);
    point rightmost = getRightmostHighestPoint(p);

    vector<point> upperHalf;
    vector<point> lowerHalf;

    for (int i = 0; i < p.size(); i++) {
        if (getOrientation(leftmost, rightmost, p[i]) == 1)
            lowerHalf.push_back(p[i]);
        else if (getOrientation(leftmost, rightmost, p[i]) == 2)
            upperHalf.push_back(p[i]);
    }

    vector<point> upperHull = FindHull(lowerHalf, leftmost, rightmost);
    vector<point> lowerHull = FindHull(upperHalf, rightmost, leftmost);

    hull.push_back(leftmost);

    for (int i = 0; i < lowerHull.size(); i++)
        hull.push_back(lowerHull[i]);

    hull.push_back(rightmost);

    for (int i = 0; i < upperHull.size(); i++)
        hull.push_back(upperHull[i]);

    return hull;
}

vector<point> ParallelFindHull(const vector<point>& p, point leftmost, point rightmost) {
    if (p.empty())
        return vector<point>(0);

    point farthest = getFarthestFromLine(p, leftmost, rightmost);

    vector<point> leftSide;
    vector<point> rightSide;

    for (int i = 0; i < p.size(); i++) {
        if (getOrientation(rightmost, farthest, p[i]) == 1)
            rightSide.push_back(p[i]);
        else if (getOrientation(leftmost, farthest, p[i]) == 2)
            leftSide.push_back(p[i]);
    }

    vector<point> leftHull = cilk_spawn ParallelFindHull(leftSide, leftmost, farthest);
    vector<point> rightHull = ParallelFindHull(rightSide, farthest, rightmost);
    cilk_sync;

    vector<point> hull;
    for (int i = 0; i < leftHull.size(); i++)
        hull.push_back(leftHull[i]);

    hull.push_back(farthest);

    for (int i = 0; i < rightHull.size(); i++)
        hull.push_back(rightHull[i]);    

    return hull;
}

vector<point> ParallelQuickHull(const vector<point>& p) {
    vector<point> hull;

    point leftmost = getLeftmostLowestPoint(p);
    point rightmost = getRightmostHighestPoint(p);

    vector<point> upperHalf;
    vector<point> lowerHalf;

    for (int i = 0; i < p.size(); i++) {
        if (getOrientation(leftmost, rightmost, p[i]) == 1)
            lowerHalf.push_back(p[i]);
        else if (getOrientation(leftmost, rightmost, p[i]) == 2)
            upperHalf.push_back(p[i]);
    }

    vector<point> upperHull = cilk_spawn ParallelFindHull(lowerHalf, leftmost, rightmost);
    vector<point> lowerHull = ParallelFindHull(upperHalf, rightmost, leftmost);
    cilk_sync;

    hull.push_back(leftmost);

    for (int i = 0; i < lowerHull.size(); i++)
        hull.push_back(lowerHull[i]);

    hull.push_back(rightmost);

    for (int i = 0; i < upperHull.size(); i++)
        hull.push_back(upperHull[i]);

    return hull;
}

#endif