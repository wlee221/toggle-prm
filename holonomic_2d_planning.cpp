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
#include "classes/graph.hpp"
#include "holonomic_2d_scenario.hpp"

using Scenario = Holonomic2DScenario;
using namespace std;

struct Options {
public:
    string file_path;

    bool argumnets_are_valid() {
        return  file_path != "";
    }

    friend ostream& operator<<(ostream &strm, const Options &o) {
        return strm;   
    }
};

int main(int argc, char* argv[]) {
    int c;
    opterr = 0;
    Options o; // store arguments
    while ((c = getopt(argc, argv, "f:n:")) != -1) {
        switch(c) {
        case 'f':
            o.file_path = optarg;
            break;
        case '?':
            cerr << "Error: invalid argument." << endl;
            break;
        }   
    }

    cout << o << endl;

    int width, height;
    int n_circles, n_rects;

    vector<Circle> circles;
    vector<Rect> rects;

    ifstream input(o.file_path);
    if (!input.is_open()) {
        cerr << "ERROR: file could not be opened." << endl;
        return 0;
    }

    input >> width >> height >> n_circles >> n_rects;
    for (int i = 0; i < n_circles; ++i) {
        float rx, ry, r;
        input >> rx >> ry >> r;
        circles.push_back(Circle(Point(rx, ry), r));
    }
    for (int i = 0; i < n_rects; ++i) {
        float x0, y0, x1, y1;
        input >> x0 >> y0 >> x1 >> y1;
        rects.push_back(Rect(Point(x0, y0), Point(x1, y1)));
    }

    Point start = Point(30, 30);
    Point goal = Point(width - 30, height - 30); 
    Scenario scenario = Scenario(width, height, circles, rects);

    const std::string filename = "holonomic_demo_output.svg";
    std::ofstream file(filename);
    svg::startSVG(file, width, height);
    for (const auto &r: rects) 
        file << r;
    for (const auto &c: circles) 
        file << c;
    svg::endSVG(file);
    return 0;

}
#endif