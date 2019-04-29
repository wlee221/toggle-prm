#ifndef HOLONOMIC_2D_SCENARIO
#define HOLONOMIC_2D_SCENARIO

#include "classes/point.hpp"
#include <vector>
#include <png.h>
#include <tuple>
#include <assert.h>

using namespace std;

class Holonomic2DScenario {
public:
    Holonomic2DScenario(int width, int height, std::vector<bool> &obstacles) 
        : width_(width), height_(height), obstacles_(obstacles)
    {
    }

    bool valid(const Point &p, bool toggle = false) const {
        int idx = width_ * (int) (p.y() + 0.5) + (int) (p.x() + 0.5);
        bool valid = !obstacles_[idx];
        return toggle ? !valid : valid;
    }

    bool link(const Point &a, const Point &b, std::vector<Point> &witness, bool toggle = false) const {
        Point mid = (a + b) / 2;
        // cout << mid.x() << ", " << mid.y() << endl;
        float distsq = dist_squared(a, b);
        float tol = 2;
        if (distsq < tol * tol)
            return true;
        if (!valid(mid, toggle)){
            witness.push_back(mid);
            return false;
        }
        if (!link(a, mid, witness, toggle))
            return false;
        return link(mid, b, witness, toggle);
    }

    std::pair<Point, Point> bounds() const {
        return make_pair(Point(0, 0), Point(width_, height_));
    }

    void test() {
        assert(valid(Point(0, 0), false));
        assert(valid(Point(500, 250), false));
        assert(!valid(Point(500, 250), true));
        std::vector<Point> t;
        assert(valid(Point(0, 0), false));
        assert(valid(Point(20, 20), false));
        assert(valid(Point(2.5, 2.5), false));
        assert(link(Point(0, 0), Point(20, 20), t, false));
    }


private:
    const int width_;
    const int height_;
    const std::vector<bool> obstacles_;
};

inline std::tuple<std::vector<bool>, int, int> readAndFilterPng(const std::string &inputName) {
    /*
     * Read png file
     */
    FILE *fp = std::fopen(inputName.c_str(), "rb");
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);

    png_init_io(png, fp);
    png_read_info(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth  = png_get_bit_depth(png, info);

    // resolve pallete img to rgb
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    // restrict 1 byte per pixel
    if (bit_depth == 16)
        png_set_strip_16(png);
    if (bit_depth < 8)
        png_set_packing(png);

    // fill alpha channel
    if (color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
    // update the changes
    png_read_update_info(png, info);

    /*
     * allocate the bitmap
     */
    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    int rowBytes = png_get_rowbytes(png, info);
    bit_depth  = png_get_bit_depth(png, info);

    std::vector<png_bytep> rowPointers(height);
    std::vector<png_byte> image(rowBytes * height);
    for (int y = 0 ; y < height ; ++y)
        rowPointers[y] = &image[y * rowBytes];
    png_read_image(png, rowPointers.data());
    fclose(fp);

    /*
     * filter the obstacle colors
     */
    std::vector<bool> obstacles;
    obstacles.reserve(width * height);
    for (int y = 0; y < height; y++)
    {
        png_bytep row = rowPointers[y];
        for (int x = 0; x < width; x++)
        {
            png_bytep px = &(row[x * 4]);
            bool isObstacle = true;
            int r = (int) px[0] * (int) px[3] / 255;
            int g = (int) px[1] * (int) px[3] / 255;
            int b = (int) px[2] * (int) px[3] / 255;
            if (r > 250 && g > 250 && b > 250)
                isObstacle = false;
            obstacles.push_back(isObstacle);
        }
    }

    png_destroy_read_struct(&png, &info, NULL);
    return std::make_tuple(obstacles, width, height);
}

#endif