#include <fstream>
#include <sys/stat.h>
#include <iostream>
#include <stdlib.h>

#ifdef _WIN32
#include <direct.h>
#endif

#include "pwanutils.h"
#include "pwanstrings.h"

std::string pwan::getextention(const std::string& filename)
{
    std::vector<std::string> exfilename = pwan::strings::explode(filename, ".");
    if(exfilename.size() > 1)
        return *(exfilename.end() -1);
    else
        return "";
}

float pwan::calculatezoom(int imagedims[2], int displaydims[2])
{
    float returnvalue;
    float tempzoom1 = (float)displaydims[0]  / (float)imagedims[0];
    float tempzoom2 = (float)displaydims[1] / (float)imagedims[1];
    if (tempzoom1 < tempzoom2)
        returnvalue = tempzoom1;
    else
        returnvalue = tempzoom2;

    return returnvalue;
}

pwan::doubleint pwan::calculateoffset(int imagedims[2], int displaydims[2])
{
    pwan::doubleint returnvalue;
    returnvalue.x = ((displaydims[0]/2) - (imagedims[0]/2));
    returnvalue.y = ((displaydims[1]/2) - (imagedims[1]/2));

    if(returnvalue.x < 0)
        returnvalue.x = 0;
    if(returnvalue.y < 0)
        returnvalue.y = 0;
    return returnvalue;
}

std::string pwan::readFile(const std::string filename)
{
    std::ifstream inputfile;
    std::string returnvalue, line;
    inputfile.open(filename.c_str());
    if (!inputfile.is_open())
        return "";
    while (!inputfile.eof())
    {
        getline(inputfile, line);
        returnvalue += line + "\n";
    }
    inputfile.close();
    return returnvalue;
}

std::vector<std::string> pwan::parsebrackets(const std::string url)
{
    static std::vector<std::string> returnvalue;
    size_t startnumber, endnumber, noDigits;
    std::string::size_type startbracket, endbracket, separator;
    std::string parsedNumber, newUrl;

    startbracket = url.find_first_of("[");
    if (startbracket != std::string::npos)
    {
        endbracket = url.find_first_of("]", startbracket);
        if (endbracket != std::string::npos)
        {
            separator = url.find_first_of("-", startbracket);
            if (separator != std::string::npos && separator < endbracket)
            {
                parsedNumber = url.substr(startbracket +1, separator - startbracket -1);
                noDigits = parsedNumber.size();
                startnumber = atoi(parsedNumber.c_str());
                parsedNumber = url.substr(separator + 1, endbracket - separator - 1);
                endnumber = atoi(parsedNumber.c_str());

                for (size_t teller = startnumber; teller != endnumber +1; ++teller)
                {
                    parsedNumber = pwan::strings::fromInt(teller, noDigits);
                    newUrl = url.substr(0, startbracket) + parsedNumber + url.substr(endbracket +1, url.size());
                    parsebrackets(newUrl);
                }
            }
        }
    }
    else
        returnvalue.push_back(url);
    return(returnvalue);
}

int pwan::writefile(const std::string filename, const char data[], const int datasize, const int writemode)
{
    std::ofstream outputfile;
    std::string::size_type dataPosition = 0;
    while(1)
    {
        dataPosition = filename.find("/", dataPosition);
        if (dataPosition == std::string::npos)
            break;
        dataPosition++;
#ifdef linux
        mkdir(filename.substr(0, dataPosition).c_str(), 0755);
#endif
#ifdef _WIN32
        _mkdir(filename.substr(0, dataPosition).c_str());
#endif

	}
    if (writemode == 0)
        outputfile.open(filename.c_str(), std::ios::out | std::ios::binary);
    else
        outputfile.open(filename.c_str(), std::ios::out | std::ios::app | std::ios::binary);
    if (!outputfile.is_open())
    {
        std::cout << "Failed to open file for writing: " << filename << std::endl;
        return(1);
    }
    outputfile.write(data, datasize);
    outputfile.close();
    return(0);
}

std::vector<std::string> pwan::html::getImageLinks(std::string filename)
{
    std::vector<std::string> returnvalue;
    std::string::size_type index, endurl;
    std::string url, data, dataLower;

    index = 0;
    if(!filename.empty())
    {
        data = pwan::readFile(filename);
        if(data.empty())
            return returnvalue;
        dataLower = pwan::strings::toLower(data);
        while(1)
        {
            index = dataLower.find("<img ", index);
            if (index == std::string::npos)
                break;

            index = dataLower.find("src=\"", index);
            if (index != std::string::npos)
            {
                index += 5;

                endurl = dataLower.find("\"", index);
                if (endurl != std::string::npos)
                {
                    url = data.substr(index, endurl - index);
                    if (!url.empty())
                        returnvalue.push_back(url);
                }
            }
        }
    }
    return returnvalue;
}

std::vector<std::string> pwan::html::getLinks(std::string filename)
{
    std::vector<std::string> returnvalue;
    std::string::size_type index, endurl;
    std::string url, data, dataLower;

    index = 0;
    if(!filename.empty())
    {
        data = pwan::readFile(filename);
        if(data.empty())
            return returnvalue;
        dataLower = pwan::strings::toLower(data);
        while(1)
        {
            index = dataLower.find("<a href=", index);
            if (index == std::string::npos)
                break;

            index += 9;
            endurl = dataLower.find("\"", index);
            if (endurl != std::string::npos)
            {
                url = data.substr(index, endurl - index);
                if (!url.empty())
                    returnvalue.push_back(url);
            }
        }
    }
    return returnvalue;
}
