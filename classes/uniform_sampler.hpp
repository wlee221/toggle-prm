#ifndef UNIFORM_SAMPLER
#define UNIFORM_SAMPLER
#include <random>
#include <cstdio>
#include "point.hpp"

class UniformSampler {
public:
    UniformSampler(int width, int height) 
        : rng_x_(rd_()), uni_x_(0, width), rng_y_(rd_()), uni_y_(0, height)
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