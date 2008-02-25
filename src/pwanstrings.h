#ifndef PWANSTRINGS_H
#define PWANSTRINGS_H

#include <string>
#include <vector>
#include <iostream>

namespace pwan
{
    namespace strings
    {
        std::string                     fromInt(long long int number, int padding = 0, int base = 10);
        std::vector<std::string>        explode(std::string inputstring, std::string explodeby = " ");
        std::string                     toLower(std::string inputstring);
        std::string                     base64Encode(const std::string text);
        std::vector<char>               dupechar(const char character, unsigned int times);
    }
}

#endif
