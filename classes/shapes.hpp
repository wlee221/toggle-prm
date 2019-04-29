#ifndef PRIMTIVES
#define PRIMTIVES

#include "point.hpp"
#include "svg.hpp"
#include <vector>
#include <iostream>

using namespace std;

constexpr float TOL = 1.0; // tolerance used in bisection methods.

class Rect {
public:
    Rect(Point p0, Point p1)
        : p0_(p0), p1_(p1)
    {
        if (!(p0.x() < p1.x() && p0.y() < p1.y()))
            cerr << "ERROR (Rect initialization): p0 and p1 must be top left and bottom right corner of rect." << endl;
    } 

    bool valid(const Point &p, bool toggle = false) const {
        float px = p.x();
        float py = p.y();
        bool valid = !(px >= p0_.x() && px <= p1_.x() && py >= p0_.y() && py <= p1_.y());
        if (toggle) 
            return !valid;
        else 
            return valid;
    }

    bool link(const Point &a, const Point &b, std::vector<Point> &witness, bool toggle = false) const {
        Point mid = (a + b) / 2;
        float distsq = (b - a).squared_norm();
        if (distsq < TOL * TOL)
            return true;
        if (!valid(mid, toggle)){
            witness.push_back(mid);
            return false;
        }
        if (!link(a, mid, witness, toggle))
            return false;
        return link(mid, b, witness, toggle);
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

#endif