#include "pwanutils.h"

std::string pwan::inttostring(long long int number, int padding, int base)
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

stringvector pwan::explodestring(std::string inputstring, std::string explodeby)
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

std::string pwan::getextention(std::string filename)
{
    std::vector<std::string> exfilename = pwan::explodestring(filename, ".");
    if(exfilename.size() > 1)
        return *(exfilename.end() -1);
    else
        return "";
}

std::string pwan::stringtolower(std::string inputstring)
{
    for(unsigned int i=0; i!=inputstring.size(); ++i)
    {
        inputstring[i] = std::tolower(inputstring[i]);
    }
    return inputstring;
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

pwan::options::options(void)
{

}

int pwan::options::set(std::string name, std::string value)
{
    internalData[name] = value;
    return 0;
}

std::string pwan::options::get(std::string name)
{
    if(internalData.find(name) != internalData.end())
        return (*(internalData.find(name))).second;
    else
        return "";
}

std::list<std::string> pwan::options::dump(void)
{
    std::list<std::string> returnvalue;
    for(std::map<std::string, std::string>::iterator iter = internalData.begin(); iter != internalData.end(); ++iter)
    {
        returnvalue.push_back((*iter).first);
        returnvalue.push_back((*iter).second);
    }
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

stringvector pwan::parsebrackets(const std::string url)
{
    static stringvector returnvalue;
    int startnumber, endnumber, noDigits;
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

                for (int teller = startnumber; teller != endnumber +1; ++teller)
                {
                    parsedNumber = inttostring(teller, noDigits);
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

std::string pwan::base64Encode(const std::string text)
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
        mkdir(filename.substr(0, dataPosition).c_str(), 0755);
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

stringvector pwan::html::getImageLinks(std::string filename)
{
    stringvector returnvalue;
    std::string::size_type index, endurl;
    std::string url, data, dataLower;

    index = 0;
    if(!filename.empty())
    {
        data = pwan::readFile(filename);
        if(data.empty())
            return returnvalue;
        dataLower = pwan::stringtolower(data);
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

stringvector pwan::html::getLinks(std::string filename)
{
    stringvector returnvalue;
    std::string::size_type index, endurl;
    std::string url, data, dataLower;

    index = 0;
    if(!filename.empty())
    {
        data = pwan::readFile(filename);
        if(data.empty())
            return returnvalue;
        dataLower = pwan::stringtolower(data);
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
