#include "pwanstrings.h"

std::string pwan::strings::fromInt(long long int number, int padding, int base)
{
    std::string::size_type returnvaluelength;
    if(base < 2 && base > 36)
    {
        std::cout << "pwan::inttostring: base not in range\n\n";
        exit(1);
    }
    std::string numbers = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string returnvalue = "";
    while(1)
    {
        long long int remainder = number % base;
        returnvalue = numbers.at(remainder) + returnvalue;
        number = number / base;
        if(!number)
            break;
    }
    returnvaluelength = returnvalue.size();
    for (int i = 0; i < (int)((padding - (int)returnvaluelength)); ++i)
        returnvalue = "0" + returnvalue;
    return returnvalue;
}

std::vector<std::string> pwan::strings::explode(std::string inputstring, std::string explodeby)
{
    std::vector<std::string> returnvalue;
    std::string::size_type start = 0;
    std::string::size_type end = 0;

    while(1)
    {
        end = inputstring.find_first_of(explodeby, start);
        if(end == std::string::npos)
        {
            returnvalue.push_back(inputstring.substr(start));
            return returnvalue;
        }
        returnvalue.push_back(inputstring.substr(start, end-start));
        start = end +1 ;
    }
    return returnvalue;
}

std::string pwan::strings::toLower(std::string inputstring)
{
    for(unsigned int i=0; i!=inputstring.size(); ++i)
    {
        inputstring[i] = std::tolower(inputstring[i]);
    }
    return inputstring;
}

std::string pwan::strings::base64Encode(const std::string text)
{
    std::string base64list = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string buffer;
    char *temptext64;
    temptext64 = new char[text.size() * 2 + 5];
    int teller;
    div_t q = div(text.length(), 3);
//    cout << q.quot << " " << q.rem << endl;
    for (teller = 0; teller < q.quot; teller++)
    {
        buffer[0] = text[teller*3];
        buffer[1] = text[(teller*3)+1];
        buffer[2] = text[(teller*3)+2];
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
//    cout << text64 << endl;
    return (text64);
}

std::vector<char> pwan::strings::dupechar(const char character, unsigned int times)
{
    std::cout << "times: " << times << "\n";
    std::vector<char> returnValue;
    for (unsigned int i = 0; i != times; ++i)
    {
        returnValue.push_back(character);
    }
    return returnValue;
}
