#ifndef PWANSTRINGS_H
#define PWANSTRINGS_H

#include <string>
#include <vector>
#include <boost/cstdint.hpp>

namespace pwan
{
    namespace strings
    {
        std::string                     fromInt(boost::int64_t number, boost::uint8_t padding = 0, boost::uint8_t base = 10);
        std::vector<std::string>        explode(const std::string& inputstring, std::string explodeby = " ");
        std::string                     toLower(std::string inputstring);
        std::string                     base64Encode(const std::string &text);
        std::vector<char>               dupechar(const char character, unsigned int times);
    }
}

#endif
