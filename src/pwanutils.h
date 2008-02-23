#ifndef PWANUTILS_H
#define PWANUTILS_H

#include <vector>
#include <string>
#include <map>
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
    
    class options
    {
        public:
            options(void);
            int set(std::string name, std::string value);
            std::string get(std::string name);

        private:
            std::map<std::string, std::string> internalData;
    };
    
    std::string inttostring(long long int number, int padding = 0, int base = 10);
    stringvector explodestring(std::string inputstring, std::string explodeby = " ");
    std::string getextention(std::string filename);
    std::string stringtolower(std::string inputstring);
    float calculatezoom(int imagedims[2], int displaydims[2]);
    doubleint calculateoffset(int imagedims[2], int displaydims[2]);
}

#endif
