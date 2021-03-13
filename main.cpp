#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "get_time.h"

#include "Point.h"
#include "GiftWrapping.h"
#include "GrahamScan.h"
#include "QuickHull.h"
#include "MonotoneChain.h"
#include "ChansAlgorithm.h"

using namespace std;

int main() {
    vector<double> regularTimes(6, 0.0);
    vector<double> optimizedTimesQuad(6, 0.0);
    vector<double> optimizedTimesOctagon(6, 0.0);

    vector<point> p;
    srand (time(NULL));

    for (int i = 0; i < 10000000; i++)
        p.push_back(point(rand() % 20000000, rand() % 20000000));

    vector<point> convexHull;

    timer t;

    t.start();
    convexHull = GiftWrapping(p);
    t.stop();
    regularTimes[0] += t.get_total();
    t.reset();

    t.start();
    convexHull = GrahamScan(p);
    t.stop();
    regularTimes[1] += t.get_total();
    t.reset();

    t.start();
    convexHull = QuickHull(p);
    t.stop();
    regularTimes[2] += t.get_total();
    t.reset();

    t.start();
    convexHull = MonotoneChain(p);
    t.stop();
    regularTimes[3] += t.get_total();
    t.reset();

    t.start();
    convexHull = ChansAlgorithm(p);
    t.stop();
    regularTimes[4] += t.get_total();
    t.reset();

    t.start();
    convexHull = ParallelQuickHull(p);
    t.stop();
    regularTimes[5] += t.get_total();
    t.reset();

    cout << "GiftWrapping Time: " << regularTimes[0] << endl;
    cout << "GrahamScan Time: " << regularTimes[1] << endl;
    cout << "QuickHull Time: " << regularTimes[2] << endl;
    cout << "MonotoneChain Time: " << regularTimes[3] << endl;
    cout << "ChansAlgorithm Time: " << regularTimes[4] << endl;
    cout << "ParallelQuickHull Time: " << regularTimes[5] << endl;

    p.clear();
    vector<point> optimizedPQuad;
    srand (time(NULL));

    for (int i = 0; i < 10000000; i++)
        p.push_back(point(rand() % 20000000, rand() % 20000000));

    t.start();
    optimizedPQuad = removeNonConvexHullPointsQuad(p);
    convexHull = GiftWrapping(optimizedPQuad);
    t.stop();
    optimizedTimesQuad[0] += t.get_total();
    t.reset();

    t.start();
    optimizedPQuad = removeNonConvexHullPointsQuad(p);
    convexHull = GrahamScan(optimizedPQuad);
    t.stop();
    optimizedTimesQuad[1] += t.get_total();
    t.reset();

    t.start();
    optimizedPQuad = removeNonConvexHullPointsQuad(p);
    convexHull = QuickHull(optimizedPQuad);
    t.stop();
    optimizedTimesQuad[2] += t.get_total();
    t.reset();

    t.start();
    optimizedPQuad = removeNonConvexHullPointsQuad(p);
    convexHull = MonotoneChain(optimizedPQuad);
    t.stop();
    optimizedTimesQuad[3] += t.get_total();
    t.reset();

    t.start();
    optimizedPQuad = removeNonConvexHullPointsQuad(p);
    convexHull = ChansAlgorithm(optimizedPQuad);
    t.stop();
    optimizedTimesQuad[4] += t.get_total();
    t.reset();

    t.start();
    optimizedPQuad = removeNonConvexHullPointsQuad(p);
    convexHull = ParallelQuickHull(optimizedPQuad);
    t.stop();
    optimizedTimesQuad[5] += t.get_total();
    t.reset();

    cout << "Optimized Quad GiftWrapping Time: " << optimizedTimesQuad[0] << endl;
    cout << "Optimized Quad GrahamScan Time: " << optimizedTimesQuad[1] << endl;
    cout << "Optimized Quad QuickHull Time: " << optimizedTimesQuad[2] << endl;
    cout << "Optimized Quad MonotoneChain Time: " << optimizedTimesQuad[3] << endl;
    cout << "Optimized Quad ChansAlgorithm Time: " << optimizedTimesQuad[4] << endl;
    cout << "Optimized Quad ParallelQuickHull Time: " << optimizedTimesQuad[5] << endl;

    p.clear();
    vector<point> optimizedPOctagon;
    srand (time(NULL));

    for (int i = 0; i < 10000000; i++)
        p.push_back(point(rand() % 20000000, rand() % 20000000));

    t.start();
    optimizedPOctagon = removeNonConvexHullPointsOctagon(p);
    convexHull = GiftWrapping(optimizedPOctagon);
    t.stop();
    optimizedTimesOctagon[0] += t.get_total();
    t.reset();

    t.start();
    optimizedPOctagon = removeNonConvexHullPointsOctagon(p);
    convexHull = GrahamScan(optimizedPOctagon);
    t.stop();
    optimizedTimesOctagon[1] += t.get_total();
    t.reset();

    t.start();
    optimizedPOctagon = removeNonConvexHullPointsOctagon(p);
    convexHull = QuickHull(optimizedPOctagon);
    t.stop();
    optimizedTimesOctagon[2] += t.get_total();
    t.reset();

    t.start();
    optimizedPOctagon = removeNonConvexHullPointsOctagon(p);
    convexHull = MonotoneChain(optimizedPOctagon);
    t.stop();
    optimizedTimesOctagon[3] += t.get_total();
    t.reset();

    t.start();
    optimizedPOctagon = removeNonConvexHullPointsOctagon(p);
    convexHull = ChansAlgorithm(optimizedPOctagon);
    t.stop();
    optimizedTimesOctagon[4] += t.get_total();
    t.reset();

    t.start();
    optimizedPOctagon = removeNonConvexHullPointsOctagon(p);
    convexHull = ParallelQuickHull(optimizedPOctagon);
    t.stop();
    optimizedTimesOctagon[5] += t.get_total();
    t.reset();

    cout << "Optimized Octagon GiftWrapping Time: " << optimizedTimesOctagon[0] << endl;
    cout << "Optimized Octagon GrahamScan Time: " << optimizedTimesOctagon[1] << endl;
    cout << "Optimized Octagon QuickHull Time: " << optimizedTimesOctagon[2] << endl;
    cout << "Optimized Octagon MonotoneChain Time: " << optimizedTimesOctagon[3] << endl;
    cout << "Optimized Octagon ChansAlgorithm Time: " << optimizedTimesOctagon[4] << endl;
    cout << "Optimized Octagon ParallelQuickHull Time: " << optimizedTimesOctagon[5] << endl;

    return 0;
}