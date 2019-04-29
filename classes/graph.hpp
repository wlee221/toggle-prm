#ifndef GRAPH
#define GRAPH
#include "point.hpp"
#include "svg.hpp"
#include <vector>
#include <set>
#include <cstdio>
#include <optional>
#include <limits>

class Graph {
public:
    Graph() {}; 

    void add_vertex(Point p) {
        int idx = vertex_.size();
        vertex_.push_back(p);
        edges_.push_back(std::set<int>());
        cc_.push_back(std::set<int> {idx});
    }

    void add_edge(int i, int j) {
        // update adjacency list
        edges_[i].insert(j);
        edges_[j].insert(i);
        // update connected components, ie. union cc_[i] and cc_[j].
        cc_[i].insert(cc_[j].begin(), cc_[j].end());
        cc_[j] = cc_[i]; // TODO: avoid copy assignment here. (perhaps using unique_ptr)
    }

    int size() {
        return vertex_.size();
    }

    float penalized_dist(int i, int j) {
        float dist = dist_squared(vertex_[i], vertex_[j]);
        if (!cc_[i].count(j) > 0)
            dist /= 16.0; // prefer nodes from different connected components
        return dist;
    }


    std::vector<int> knearest(int k, int idx) {
        std::vector<int> arr;
        arr.reserve(k + 1);
        for (int i = 0; i < vertex_.size(); ++i) {
            if (i == idx) 
                continue;
            if (arr.size() <= k) {
                arr.push_back(i);
            }
            else {
                arr[k] = i;
            }

            for (int j = arr.size() - 1; j > 0; j--) 
                if (penalized_dist(idx, arr[j]) < penalized_dist(idx, arr[j - 1]))
                    std::swap(arr[j-1], arr[j]);
                else 
                    break;
        }
        if (arr.size() > k)
            arr.pop_back();
        return arr;
    }
    template <typename Scenario>
    std::vector<Point> connect(int k, const Scenario &s, bool toggle = false) {
        // last two parameters are only applicable for TogglePRM. So use optional parameters.
        std::vector<Point> witness;
        for (int i = 0; i < vertex_.size(); ++i) {
            std::vector<int> candidates = knearest(k, i);
            for (const auto &j : candidates) {
                Point from = vertex_[i];
                Point to = vertex_[j];
                if (s.link(from, to, witness, toggle)) {
                    add_edge(i, j);
                }
            }
        }

        return witness;
    }

    // debug function 
    template <typename T>
    void print(T set) {
        std::cout << "[ ";
        for (const auto &i : set) 
            std::cout << i << " ";
        std::cout << "]\n";
    }

    void draw_path(std::ostream &strm, bool draw_solution = true) {
        for(int i = 0; i < vertex_.size(); ++i) {
            std::set<int> set = edges_[i];
            for (const auto &j : set) {
                svg::addEdge(strm, vertex_[i].x(), vertex_[i].y(), vertex_[j].x(), vertex_[j].y(), 0.5);
            }
        }
        if (draw_solution) {
            auto solution_path = shortest_path();
            if (!solution_path.has_value()) {
                std::cerr << "No solution was found." << endl;
                return;
            }
            std::vector<int> path = solution_path.value();
            int u = 1;
            while (path[u] != -1) {
                svg::addSolutionEdge(strm, vertex_[u].x(), vertex_[u].y(), vertex_[path[u]].x(), vertex_[path[u]].y(), 2.0);
                u = path[u];
            }
        }
    }

    // TODO: extract this to a separate file
    // if shortest path exists, return the shortest path. Return {} otherwise.
    std::optional<std::vector<int>> shortest_path() {
        if (vertex_.size() == 0)
            return {};
        std::set<int> q;
        std::vector<float> dist;
        std::vector<int> prev;

        float inf = std::numeric_limits<float>::infinity();

        for (int i = 0; i < vertex_.size(); ++i) {
            q.insert(i);
            dist.push_back(inf);
            prev.push_back(-1);
        }

        dist[0] = 0;

        while (q.size() > 0) {
            float min_dist = inf;
            int min_idx = -1;

            for (const auto &i : q) {
                if (dist[i] < min_dist) {
                    min_idx = i;
                    min_dist = dist[i];
                }
            }

            int u = min_idx;
            if (u == -1) 
                break;
            q.erase(u);

            for (const auto &v : edges_[u]) {
                float alt = dist[u] + dist_squared(vertex_[u], vertex_[v]);
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                }
            }
        }
        if (prev[1] == -1) 
            return {};
        else 
            return prev;
    }

private:
    std::vector<Point> vertex_;
    std::vector<std::set<int>> edges_; // adjacency list
    std::vector<std::set<int>> cc_; // connected components
};


#endif