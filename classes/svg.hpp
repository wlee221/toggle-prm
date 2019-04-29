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
} 

#endif