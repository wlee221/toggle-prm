#ifndef POINT 
#define POINT

class Point {
public:
    Point(float x, float y)
        : x_(x), y_(y)
    {
    }

    float x() const {
        return x_;
    }

    float y() const {
        return y_;
    }

    // l2 norm squared
    float squared_norm() {
        return x_ * x_ + y_ * y_;
    }

    float dot(const Point &p) {
        return this->x() * p.x() + this->y() * p.y();
    }

private:
    float x_;
    float y_;
};

inline Point operator+ (const Point& lhs, const Point& rhs) {
    return Point(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}

inline Point operator- (const Point& lhs, const Point& rhs) {
    return Point(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}

inline Point operator/ (const Point &p, float d) {
    return Point(p.x() / d, p.y() / d);
}

inline Point operator* (const Point &p, float d) {
    return Point(p.x() * d, p.y() * d);
}

/* Unnecessary
inline Point operator/ (const Point &p, int d) {
    return Point(p.x() / (float) d, p.y() / (float) d);
}
*/

inline bool operator==(const Point& lhs, const Point& rhs) { 
    return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

inline float dist_squared(Point p, Point q) {
    return (p.x() - q.x()) * (p.x() - q.x()) + (p.y() - q.y()) * (p.y() - q.y());
}

inline float point_segment_distance_squared(const Point &pt, const Point &s0, const Point &s1) {
    Point v = s1 - s0;
    Point w = pt - s0;
    float c1 = v.dot(w);
    if (c1 <= 0)
        return w.squared_norm();
    float c2 = v.squared_norm();
    if (c2 <= c1)
        return (pt - s1).squared_norm();
    return (s0 - pt + v * (c1 / c2)).squared_norm();
}

#endif