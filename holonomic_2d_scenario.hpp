#ifndef HOLONOMIC_2D_SCENARIO
#define HOLONOMIC_2D_SCENARIO

#include "classes/point.hpp"
#include "classes/shapes.hpp"
#include <vector>

using namespace std;

class Holonomic2DScenario {
public:
    Holonomic2DScenario(int width, int height, const vector<Circle> &circles, const vector<Rect> &rects) 
        : width_(width), height_(height), circles_(circles), rects_(rects)
    {
    }

    bool valid(const Point &p, bool toggle = false) const {
        for (const auto &c : circles_)
            if (!c.valid(p))
                return false;
        for (const auto &r : rects_)
            if (!r.valid(p))
                return false;
        return true;
    }

    bool link(const Point &a, const Point &b, bool toggle = false) const {
        for (const auto &c : circles_)
            if (!c.link(a, b))
                return false;
        for (const auto &r : rects_)
            if (!r.link(a, b))
                return false;
        return true;
    }

    std::pair<Point, Point> bounds() const {
        return make_pair(Point(0, 0), Point(width_, height_));
    }

private:
    const int width_;
    const int height_;
    const vector<Circle> &circles_;
    const vector<Rect> &rects_;
};

#endif