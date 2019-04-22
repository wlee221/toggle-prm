#ifndef PRIMTIVES
#define PRIMTIVES

#include "point.hpp"
#include "svg.hpp"
#include <iostream>

using namespace std;

constexpr float TOL = 1e-2; // tolerance used in bisection methods.

class Rect {
public:
    Rect(Point p0, Point p1)
        : p0_(p0), p1_(p1)
    {
        if (!(p0.x() < p1.x() && p0.y() < p0.y()))
            cerr << "ERROR (Rect initialization): p0 and p1 must be top left and bottom right corner of rect." << endl;
    } 

    bool valid(const Point &p) const {
        float px = p.x();
        float py = p.y();
        return !(px >= p0_.x() && px <= p1_.x() && py >= p0_.y() && py <= p1_.y());
    }

    bool link(const Point &a, const Point &b) const {
        Point mid = (a + b) / 2;
        float distsq = (b - a).squared_norm();
        if (distsq < TOL * TOL)
            return true;
        if (!valid(mid))
            return false;
        if (!link(a, mid))
            return false;
        return link(mid, b);
    }

    friend ostream &operator<<(ostream &strm, const Rect &r) {
        using namespace svg;
        addTabs(strm, 1);
        startTag(strm, "rect");
        addAttr(strm, "x", r.p0_.x());
        addAttr(strm, "y", r.p0_.y());
        addAttr(strm, "width", r.p1_.x() - r.p0_.x());
        addAttr(strm, "height", r.p1_.y() - r.p0_.y());
        addAttr(strm, "fill", "rgb(50, 50, 50");
        closeTag(strm);
    };

private:
    const Point p0_;
    const Point p1_;

};

class Circle {
public:
    Circle(Point center, float radius)
        : center_(center), radius_(radius)
    {
    }

    bool valid(const Point &p) const {
        Point dist = p - center_; // distance vector
        return dist.squared_norm() > radius_ * radius_;
    }

    bool link(const Point &a, const Point &b) const {
        return point_segment_distance_squared(center_, a, b) > radius_ * radius_;
    }

    friend ostream &operator<<(ostream &strm, const Circle &c) {
        using namespace svg;
        addTabs(strm, 1);
        startTag(strm, "circle");
        addAttr(strm, "cx", c.center_.x());
        addAttr(strm, "cy", c.center_.y());
        addAttr(strm, "r", c.radius_);
        addAttr(strm, "fill", "rgb(50, 50, 50)");
        closeTag(strm);
    };

private:
    Point center_;
    float radius_;
};

#endif