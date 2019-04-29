#ifndef PRM_HPP
#define PRM_HPP
#include "../classes/graph.hpp"
#include "../classes/point.hpp"
#include "../classes/uniform_sampler.hpp"
#include <cstdio>
#include <optional>

template <class Scenario>
class PRM {
public:
    PRM(Scenario s, int n, int k, std::optional<int> m_opt, Point start, Point goal) 
        : s_(s), n_(n), k_(k), sampler_(s.bounds()), start_(start), goal_(goal)
    {
        // add start and goal states 
        free_.add_vertex(start_);
        free_.add_vertex(goal_);
    }

    void grow_roadmap() {
        for (int i = 0; i < n_; ++i) {
            Point node = sampler_.sample();
            if (s_.valid(node)) 
                free_.add_vertex(node);
        }
        free_.connect(k_, s_);
    }

    void solve() {
        int max_iter = 10000;
        while (--max_iter) {
            grow_roadmap();
            auto solution = free_.shortest_path();
            if (solution.has_value()){
                break;
            }
        }
    }

    void draw_path(std::ostream &strm) {
        free_.draw_path(strm);
    }

private:
    const Scenario s_;
    const int n_; // number of samples per iteration
    const int k_; // k nearest neighbors
    const Point start_;
    const Point goal_;

    Graph free_; // free space roadmap
    UniformSampler sampler_;
};

#endif