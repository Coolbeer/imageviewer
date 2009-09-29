#include <stdexcept>
#include <cctype>

#include "pwanstrings.h"

std::string pwan::strings::fromInt(boost::int64_t number, boost::uint8_t padding, boost::uint8_t base)
{
    std::string::size_type returnvaluelength;
    const std::string numbers = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string returnvalue;
    bool negative = false;

    if(number < 0)
    {
        number = -number;
        negative = true;
    }
    if(base < 2 || base > 36)
        throw std::out_of_range("Base not in range");
    do
    {
		boost::uint8_t remainder = number % base;
        returnvalue = numbers.at(remainder) + returnvalue;
        number = number / base;
    } while(number);

    returnvaluelength = returnvalue.size();
    if(negative && padding)
        padding = padding -1;
    if(padding > returnvaluelength)
        returnvalue = std::string(padding - returnvaluelength, '0') + returnvalue;
    if(negative)
        returnvalue = "-" + returnvalue;
    return returnvalue;
}

std::vector<std::string> pwan::strings::explode(const std::string& inputstring, std::string explodeby)
{
    std::vector<std::string> returnvalue;
    std::string::size_type start = 0;
    std::string::size_type end;
    if(inputstring.size() != 0)
    {
        while(start != inputstring.size() && isspace(inputstring[start]))
            ++start;
        for(; start != std::string::npos; start++)
        {
            end = inputstring.find_first_of(explodeby, start);
            if(end == std::string::npos)
            {
                returnvalue.push_back(inputstring.substr(start));
                return returnvalue;
            }
            returnvalue.push_back(inputstring.substr(start, end-start));
            start = end;
        }
    }
    return returnvalue;
}

std::string pwan::strings::toLower(std::string inputstring)
{
    for(std::string::size_type i = 0; i != inputstring.size(); ++i)
    {
        inputstring[i] = (char)std::tolower(inputstring[i]);
    }
    return inputstring;
}

std::string pwan::strings::base64Encode(const std::string &text)
{
    const std::string base64list = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string buffer(3,' ');
    std::string::size_type teller;
    char *temptext64;
    div_t q = div((int)text.length(), 3);

    temptext64 = new char[text.size() * 2 + 5];
    for (teller = 0; teller < (unsigned int)q.quot; teller++)
    {
        buffer.at(0) = text[teller*3];
        buffer.at(1) = text[(teller*3)+1];
        buffer.at(2) = text[(teller*3)+2];
        temptext64[teller*4] = base64list[buffer[0] >> 2];
        temptext64[(teller*4)+1] = base64list[(buffer[0] & 0x03) << 4 | (buffer[1] & 0xf0) >> 4];
        temptext64[(teller*4)+2] = base64list[(buffer[1] & 0x0f) << 2 | (buffer[2] & 0xc0) >> 6];
        temptext64[(teller*4)+3] = base64list[(buffer[2] & 0x3f)];
    }
    if (q.rem > 0)
    {
        buffer[0] = text[(teller)*3];
        if (q.rem > 1)
            buffer[1] = text[((teller)*3)+1];
        else
            buffer[1] = '\0';
        buffer[2] = '\0';
        temptext64[(teller)*4] = base64list[buffer[0] >> 2];
        temptext64[(teller*4)+1] = base64list[(buffer[0] & 0x03) << 4 | (buffer[1] & 0xf0) >> 4];
        if (q.rem > 1)
            temptext64[(teller*4)+2] = base64list[(buffer[1] & 0x0f) << 2];
        else
            temptext64[(teller*4)+2] = '=';
        temptext64[(teller*4)+3] = '=';
    }
    temptext64[(teller*4)+4] = '\0';
    std::string text64 = temptext64;
    delete(temptext64);
    return (text64);
}

std::vector<char> pwan::strings::dupechar(const char character, unsigned int times)
{
    std::vector<char> returnValue;
    for (unsigned int i = 0; i != times; ++i)
    {
        returnValue.push_back(character);
    }
    return returnValue;
}
