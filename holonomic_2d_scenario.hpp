#ifndef HOLONOMIC_2D_SCENARIO
#define HOLONOMIC_2D_SCENARIO

#include "point.hpp"
#include "primitives.hpp"
#include <vector>

using namespace std;

class Holonomic2DScenario {
public:
	Holonomic2DScenario(int width, int height, const vector<Circle> &circles, const vector<Rect> &rects) 
		: width_(width), height_(height), circles_(circles), rects_(rects)
	{
	}

	bool valid(const Point &p, bool toggle) const {
		return true;
	}

	bool link(const Point &a, const Point &b, bool toggle) {
		return true;
	}

private:
	const int width_;
	const int height_;
	const vector<Circle> &circles_;
	const vector<Rect> &rects_;
};

#endif