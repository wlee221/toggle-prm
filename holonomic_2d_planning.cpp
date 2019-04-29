#ifndef HOLONOMIC_2D_PLANNING
#define HOLONOMIC_2D_PLANNING

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "classes/point.hpp"
#include "classes/shapes.hpp"
#include "classes/svg.hpp"
#include "algorithm/prm.hpp"
#include "algorithm/toggle_prm.hpp"
#include "holonomic_2d_scenario.hpp"

using Scenario = Holonomic2DScenario;
using Planner = TogglePRM<Scenario>; // use PRM<Scenario> for traditional PRM.
using namespace std;

// take command line inputs
struct Options {
public:
    string file_path;
    int n = -1;
    int k = -1;
    std::optional<int> m;
    int N = -1;

    bool argumnets_are_valid() {
        if (!(file_path != "" && n > 0 && k > 0 && n > k))
            return false;  
        if (m.has_value() && m.value() <= 0)
            return false;
        if (N <= 0)
            return false;
        return true;
    }
};

int main(int argc, char* argv[]) {
    int c;
    opterr = 0;
    Options o; // store arguments
    while ((c = getopt(argc, argv, "f:n:k:m:N:")) != -1) {
        switch(c) {
        case 'f':
            o.file_path = optarg;
            break;
        case 'n':
            o.n = stoi(optarg);
            break;
        case 'k':
            o.k = stoi(optarg);
            break;
        case 'm':
            o.m = stoi(optarg);
            break;
        case 'N':
            o.N = stoi(optarg);
            break;
        case '?':
            cerr << "Error: invalid flag found." << endl;
            break;
        }   
    }
    if (!o.argumnets_are_valid()) {
        cerr << "Error: invalid arguments." << endl;
        return 0;
    }

    auto [obstacles, width, height] = readAndFilterPng(o.file_path + ".png");
    ifstream input(o.file_path + ".cfg");
    float sx, sy, gx, gy;
    input >> sx >> sy >> gx >> gy; // coordinates of start and goal positions
    Point start = Point(sx, sy);
    Point goal = Point(gx, gy); 
    Scenario scenario = Scenario(width, height, obstacles);
    //scenario.test();
    Planner planner(scenario, o.n, o.k, o.m, start, goal);
    for (int i = 0; i < o.N; ++i){
        Planner planner(scenario, o.n, o.k, o.m, start, goal);
        planner.solve();
        planner.print_stats();
        #if 0 // enable this to print the result
            const std::string filename = "holonomic_demo_output.svg";
            std::ofstream file(filename);
            svg::startSVG(file, width, height);
            planner.draw_path(file);
            svg::endSVG(file);
            file.close();
        #endif
    }

    return 0;

}
#endif