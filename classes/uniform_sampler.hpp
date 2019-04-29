#ifndef UNIFORM_SAMPLER
#define UNIFORM_SAMPLER
#include <random>
#include <cstdio>
#include "point.hpp"

class UniformSampler {
public:
    UniformSampler(int x_min, int x_max, int y_min, int y_max) 
        : rng_x_(rd_()), uni_x_(x_min, x_max), rng_y_(rd_()), uni_y_(y_min, y_max)
    {
    }
    
    UniformSampler(std::pair<Point, Point> bounds)
        : UniformSampler(bounds.first.x(), bounds.second.x(), bounds.first.y(), bounds.second.y())
    {
    }

    Point sample() {
        return Point(uni_x_(rng_x_), uni_y_(rng_y_));
    }

private:
    std::random_device rd_;
    std::mt19937 rng_x_;
    std::uniform_real_distribution<float> uni_x_;
    std::mt19937 rng_y_;
    std::uniform_real_distribution<float> uni_y_;
};
#endif