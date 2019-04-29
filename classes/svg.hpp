#ifndef SVG
#define SVG

#include <iostream>
#include <fstream>

namespace svg {
    inline void addTabs(std::ostream &strm, int n) {
        while (n--) 
            strm << '\t';
    }
    inline void startTag(std::ostream &strm, std::string tag) {
        strm << "<" << tag;
    }

    inline void closeTag(std::ostream &strm) {
        strm << "/>\n";
    }

    inline void closeTag(std::ostream &strm, std::string tag) {
        strm << "</" + tag + ">\n";
    }

    template <typename T>
    inline void addAttr(std::ostream &strm, std::string name, T value, std::string unit = "") {
        strm << ' ' << name << "=" <<  "\"" << value << unit << "\"";
    }

    inline void startSVG(std::ostream &strm, int width, int height) {
        strm << "<?xml version=\"1.0\" standalone=\"no\" ?>" << std::endl
             << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << std::endl;
        startTag(strm, "svg");
        addAttr(strm, "width", width, "px");
        addAttr(strm, "height", height, "px");
        addAttr(strm, "xmlns", "http://www.w3.org/2000/svg");
        addAttr(strm, "xmlns:xlink", "http://www.w3.org/1999/xlink");
        addAttr(strm, "version", "1.1");
        strm << ">\n";        
    }

    inline void endSVG(std::ostream &strm) {
        closeTag(strm, "svg");
    }

    inline void addEdge(std::ostream &strm, float x1, float y1, float x2, float y2, float width) {
        addTabs(strm, 1);
        startTag(strm, "line");
        addAttr(strm, "x1", x1);
        addAttr(strm, "y1", y1);
        addAttr(strm, "x2", x2);
        addAttr(strm, "y2", y2);
        addAttr(strm, "stroke", "rgb(125, 125, 125)");
        addAttr(strm, "stroke-width", width);
        addAttr(strm, "stroke-linecap", "round");
        closeTag(strm);
    }

    inline void addSolutionEdge(std::ostream &strm, float x1, float y1, float x2, float y2, float width) {
        addTabs(strm, 1);
        startTag(strm, "line");
        addAttr(strm, "x1", x1);
        addAttr(strm, "y1", y1);
        addAttr(strm, "x2", x2);
        addAttr(strm, "y2", y2);
        addAttr(strm, "stroke", "rgb(255, 0, 0)");
        addAttr(strm, "stroke-width", width);
        addAttr(strm, "stroke-linecap", "round");
        closeTag(strm);
    }

} 

#endif