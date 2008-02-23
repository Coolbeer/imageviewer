#ifndef PWANUTILS_H
#define PWANUTILS_H

#include <vector>
#include <string>
#include <iostream>

typedef std::vector<std::string> stringvector;

namespace pwan
{
    class doubleint
    {
        public:
            int x;
            int y;
    };
    std::string inttostring(long long int number, int padding = 0, int base = 10);
    stringvector explodestring(std::string inputstring, std::string explodeby = " ");
    std::string getextention(std::string filename);
    std::string stringtolower(std::string inputstring);
    float calculatezoom(int imagedims[2], int displaydims[2]);
    doubleint calculateoffset(int imagedims[2], int displaydims[2]);
}

#endif
