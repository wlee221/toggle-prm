#ifndef HOLONOMIC_2D_PLANNING
#define HOLONOMIC_2D_PLANNING

#include "classes/point.hpp"
#include "classes/shapes.hpp"
#include "holonomic_2d_scenario.hpp"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

using Scenario = Holonomic2DScenario;

int main(int argc, char* argv[]) {
    if (!argc != 3)
        cerr << "Usage: " << argv[0] << " <file path> <number of runs>" << endl;

    const string file_name = argv[1];
    const int nruns = stoi(argv[2]);

    int width, height;
    int n_circles, n_rects;

    vector<Circle> circles;
    vector<Rect> rects;

    ifstream input(file_name);
    if (!input.is_open()) {
        cerr << "ERROR: file could not be opened." << endl;
        return 0;
    }

    input >> width >> height >> n_circles >> n_rects;
    for (int i = 0; i < n_circles; ++i) {
        float rx, ry, r;
        input >> rx, ry, r;
        circles.push_back(Circle(Point(rx, ry), r));
    }
    for (int i = 0; i < n_rects; ++i) {
        float x0, y0, x1, y1;
        input >> x0, y0, x1, y1;
        rects.push_back(Rect(Point(x0, x1), Point(y0, y1)));
    }

    Point start = Point(30, 30);
    Point goal = Point(width - 30, height - 30); 
    Scenario scenario = Scenario(width, height, circles, rects);

    return 0;
}

#endif