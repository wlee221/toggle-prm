#ifndef TOGGLE_PRM_HPP
#define TOGGLE_PRM_HPP
#include "../classes/graph.hpp"
#include "../classes/point.hpp"
#include "../classes/uniform_sampler.hpp"
#include <chrono> 
#include <cstdio>
#include <optional>
#include <queue>

template <class Scenario>
class TogglePRM {
public:
    TogglePRM(Scenario s, int n, int k, std::optional<int> m_opt, Point start, Point goal) 
        : s_(s), n_(n), k_(k), m_opt_(m_opt), sampler_(s.bounds()), start_(start), goal_(goal)
    {
        // add start and goal states 
        free_.add_vertex(start_);
        free_.add_vertex(goal_);
        if (m_opt_.has_value()) {
            m_ = m_opt.value();
        } else {
            m_ = 10 * n_;
            dynamic = true;
        }
    }

    void grow_roadmap() {
        std::queue<Point> queue;
        bool toggle = false;

        for (int i = 0; i < n_; ++i) {
            queue.push(sampler_.sample());
        }
        for (int i = 0; i < m_; ++i) {
            if (queue.empty()) 
                break;
            Point node = queue.front();
            queue.pop();
            if (s_.valid(node, toggle)) {
                free_.add_vertex(node);
                std::vector<Point> collision_nodes = free_.connect(k_, s_, toggle);
                for (const auto witness : collision_nodes) {
                    queue.push(witness);
                }
            } else {
                toggle = !toggle;
                obst_.add_vertex(node);
                std::vector<Point> valid_nodes = obst_.connect(k_, s_, toggle);
                for (const auto witness : valid_nodes) {
                    //std::cout << witness.x() << ", " << witness.y() << std::endl;
                    queue.push(witness);                
                }
                toggle = !toggle;
            }
        }
    }

    void solve() {
        auto start = chrono::high_resolution_clock::now(); 
        int max_iter = 1000;
        while (--max_iter) {
            grow_roadmap();
            auto solution = free_.shortest_path();
            if (solution.has_value()){
                break;
            }
        }
        auto stop = chrono::high_resolution_clock::now(); 
        duration_ = chrono::duration<float>(stop - start);
    }

    void draw_path(std::ostream &strm) {
        free_.draw_path(strm);
        obst_.draw_path(strm, false);
    }

    void print_stats() {
        std::cout   << duration_.count() << " " 
                    << free_.size() + obst_.size() << " " 
                    << ((float) free_.size() - (float) obst_.size()) / ((float) free_.size() + obst_.size()) << std::endl;
    }

private:
    const Scenario s_;
    const int n_; // number of samples per iteration
    const int k_; // k nearest neighbors
    std::optional<int> m_opt_;
    bool dynamic = false;
    int m_;
    const Point start_;
    const Point goal_;

    Graph free_; // free space roadmap
    Graph obst_; // obstacle space roadmap
    UniformSampler sampler_;
    chrono::duration<float> duration_;
};

#endif