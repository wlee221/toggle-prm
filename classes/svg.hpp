#ifndef SVG
#define SVG

#include <iostream>
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
} 

#endif