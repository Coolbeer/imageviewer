#include "pwanoptions.h"
#include "pwandebug.h"

extern pwan::debug debugz;

pwan::options::options(void)
{
    className = "pwan::options";
}

int pwan::options::set(std::string name, std::string value)
{
    std::string functionName = "set";
    debugz.print(className + "::" + functionName, name + " = " + value, 3);
    internalData[name] = value;
    return 0;
}

std::string pwan::options::get(std::string name)
{
    std::string functionName = "get";
    debugz.print(className + "::" + functionName, "name = " + name, 3);
    if(internalData.find(name) != internalData.end())
    {
        debugz.print(className + "::" + functionName, "Returning: " + (*(internalData.find(name))).second, 3);
        return (*(internalData.find(name))).second;
    }
    else
    {
        debugz.print(className + "::" + functionName, "Returning empty string(option not found) " , 3);
        return "";
    }
}

std::list<std::string> pwan::options::dump(void)
{
    std::string functionName = "dump";
    debugz.print(className + "::" + functionName, "Dumping options", 3);
    std::list<std::string> returnvalue;
    for(std::map<std::string, std::string>::iterator iter = internalData.begin(); iter != internalData.end(); ++iter)
    {
        returnvalue.push_back((*iter).first);
        returnvalue.push_back((*iter).second);
    }
    return returnvalue;
}
