#ifndef MONOTONECHAIN_H
#define MONOTONECHAIN_H

#include <vector>
#include <algorithm>
#include "Point.h"

using namespace std;

vector<point> MonotoneChain(const vector<point>& p) {
    vector<point> points = p;
	sort(points.begin(), points.end());

    vector<point> lowerHull;
    vector<point> upperHull;

	for (int i = 0; i < p.size(); i++) {
		while (lowerHull.size() >= 2 && getOrientation(lowerHull[lowerHull.size() - 2], lowerHull.back(), p[i]) <= 1)
            lowerHull.pop_back();

		lowerHull.push_back(p[i]);
	}

	for (int i = p.size() - 1; i >= 0; i--) {
		while (upperHull.size() >= 2 && getOrientation(upperHull[upperHull.size() - 2], upperHull.back(), p[i]) <= 1) 
            upperHull.pop_back();

		upperHull.push_back(p[i]);
	}

    vector<point> hull;
    for (int i = 0; i < lowerHull.size() - 1; i++) {
        hull.push_back(lowerHull[i]);
    }

    for (int i = 0; i < upperHull.size() - 1; i++) {
        hull.push_back(upperHull[i]);
    }

	return hull;
}

#endif