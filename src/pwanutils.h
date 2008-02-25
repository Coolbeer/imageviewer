#ifndef PWANUTILS_H
#define PWANUTILS_H

#include <vector>
#include <string>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include "pwanoptions.h"
#include "pwanstrings.h"

typedef std::vector<std::string> stringvector;

namespace pwan
{
    class doubleint
    {
        public:
            int x;
            int y;
    };

    namespace html
    {
        stringvector    getImageLinks(std::string filename);
        stringvector    getLinks(std::string filename);
    }

    enum fileWriteMode {OverWrite, Append};

    std::string         getextention(std::string filename);
    float               calculatezoom(int imagedims[2], int displaydims[2]);
    doubleint           calculateoffset(int imagedims[2], int displaydims[2]);

    std::string         readFile(const std::string filename);
    stringvector        parsebrackets(const std::string url);
    int                 writefile(const std::string filename, const char data[], const int datasize, const int writemode);
}

#endif
