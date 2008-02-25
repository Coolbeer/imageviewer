#include "pwanoptions.h"

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
