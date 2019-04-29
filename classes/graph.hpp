#ifndef GRAPH
#define GRAPH
#include "point.hpp"
#include <vector>
#include <set>

class Graph {
public:
    Graph();

    void add_vertex(Point p) {
        vertex_.push_back(p);
        edges_.push_back(std::vector<int>());
        cc_.push_back(std::set<int>());
    }

    void addEdge(int i, int j) {
        // update adjacency list
        edges_[i].push_back(j);
        edges_[j].push_back(i);
        // update connected components, ie. union cc_[i] and cc_[j].
        cc_[i].insert(cc_[j].begin(), cc_[j].end());
        cc_[j] = cc_[i]; // TODO: avoid copy assignment here. (perhaps using unique_ptr)
    }

private:
    std::vector<Point> vertex_;
    std::vector<std::vector<int>> edges_; // adjacency list
    std::vector<std::set<int>> cc_; // connected components
};


#endif