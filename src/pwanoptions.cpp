#include <stdexcept>
#include <fstream>

#include "pwanoptions.h"
#include "pwandebug.h"
#include "pwanstrings.h"
#include "pwantools_enums.h"

//extern pwan::debug debug;
extern unsigned int debugLevel;
pwan::options::options(void)
{
    className = "pwan::options";
    data = NULL;
}

int pwan::options::set(const std::string& name, const std::string& value)
{
    std::string functionName = "set";
    dprint(className + "::" + functionName, name + " = " + value, 3);
    if(!data)
        return P_ERROR;
    data->internalData[name] = value;
    return P_OK;
}

//TODO: Rewrite to return an enum and set the current return as a function parameter
std::string pwan::options::get(const std::string& name)
{
    std::string functionName = "get";
    dprint(className + "::" + functionName, "name = " + name, 3);
    if(!data)
        return "";

    if(data->internalData.find(name) != data->internalData.end())
    {
        dprint(className + "::" + functionName, "Returning: " + (*(data->internalData.find(name))).second, 3);
        return (*(data->internalData.find(name))).second;
    }
    else
    {
        dprint(className + "::" + functionName, "Returning empty string(option not found) " , 3);
        return "";
    }
}

//TODO Return enum, current return as parameter
std::list<std::string> pwan::options::dump(void)
{
    std::string functionName = "dump";
    dprint(className + "::" + functionName, "Dumping options", 3);
    std::list<std::string> returnvalue;
    if(!data)
        return returnvalue;

    for(std::map<std::string, std::string>::iterator iter = data->internalData.begin(); iter != data->internalData.end(); ++iter)
    {
        returnvalue.push_back((*iter).first);
        returnvalue.push_back((*iter).second);
    }
    return returnvalue;
}

pwan::p_returnValue pwan::options::setOption(const std::string& shortOpt, const std::string& longOpt, const std::string& description, const std::string& validParams)
{
    const std::string functionName("setOption");
    dprint(className + "::" + functionName, "shortOpt = \"" + shortOpt + "\", longOpt = \"" + longOpt + "\"", 3);
    if(!data)
        return P_ERROR;
    if(longOpt.empty())
        return P_ERROR;

    optionBlob newOption;
    newOption.shortOpt = shortOpt;
    newOption.longOpt = longOpt;
    newOption.description = description;
    newOption.validParams = validParams;
    data->allowedOptions.push_back(newOption);
    return P_OK;
}

std::string pwan::options::makeHelp(void)
{
    const std::string functionName("makeHelp");
    std::string returnValue;
    std::vector<optionBlob>::iterator opBlobIter;
    bool hasOpt = false;
    size_t longestShort = 0;
    size_t longestLong = 0;

    if(!data)
        return "";

    returnValue = "Usage: ";
    if(!data->programName.empty())
        returnValue += data->programName;
    else
        returnValue += "programName";
    if((data->defaultOpt != "" && data->allowedOptions.size() > 1) || (data->defaultOpt == "" && data->allowedOptions.size() > 0))
    {
        returnValue += " [OPTIONS]";
        hasOpt = true;
    }
    if(data->defaultOpt != "")
    {
        returnValue += " [" + data->defaultOpt + "]";
    }
    if(hasOpt)
    {
        returnValue += "\n\nWhere [OPTIONS] is one of the following:\n";
        for(opBlobIter = data->allowedOptions.begin(); opBlobIter != data->allowedOptions.end(); ++opBlobIter)
        {
            if(opBlobIter->shortOpt.size() > longestShort)
                longestShort = opBlobIter->shortOpt.size();
            if(opBlobIter->longOpt.size() > longestLong)
                longestLong = opBlobIter->longOpt.size();
        }
        for(opBlobIter = data->allowedOptions.begin(); opBlobIter != data->allowedOptions.end(); ++opBlobIter)
        {
            if(opBlobIter->longOpt == data->defaultOpt)
                continue;
            if(opBlobIter->shortOpt != "")
                returnValue += "  -" + opBlobIter->shortOpt + "," + std::string(longestShort - opBlobIter->shortOpt.size() + 2, ' ');
            else
                returnValue += std::string(longestShort + 6, ' ');
                returnValue += "--" + opBlobIter->longOpt + std::string(longestLong - opBlobIter->longOpt.size() + 5, ' ');
                returnValue += opBlobIter->description + "\n";
        }
    }
    returnValue += "\n";
    dprint(className + "::" + functionName, "Returning a string of " + pwan::strings::fromInt(returnValue.size()) + " bytes", 3);
    return returnValue;
}

std::vector<std::string> pwan::options::checkIniFile(const std::string& filename)
{
    const std::string functionName("checkIniFile");
    std::vector<std::string> returnValue;
    std::vector<std::string> expLine, expValOpts;
    std::string strToCheck;
    std::vector<optionBlob>::iterator opBlobIter;
    std::vector<std::string>::iterator expValOptsIter;

    if(!data)
        return returnValue;

    dprint(className + "::" + functionName, "Filename = \"" + filename + "\"", 3);
    std::fstream inputFile(filename.c_str(), std::ios::in);
    if(!inputFile.is_open())
    {
        dprint(className + "::" + functionName, "Failed to open inifile", 3);
        return returnValue;
    }
    while(std::getline(inputFile, strToCheck))
    {
        if(strToCheck.empty() || strToCheck[0] == '#')
            continue;
        expLine = pwan::strings::explode(strToCheck, "=");
        if(expLine.size() == 2)
        {
            for(opBlobIter = data->allowedOptions.begin(); opBlobIter != data->allowedOptions.end(); ++opBlobIter)
            {
                expValOpts = pwan::strings::explode(opBlobIter->validParams, ":");
                if(expLine.at(0) == opBlobIter->longOpt)
                {
                    if(opBlobIter->validParams == "!")
                    {
                        if(expLine.at(1) == "true")
                            set(expLine.at(0), "true");
                        else if(expLine.at(1) == "false")
                            set(expLine.at(0), "false");
                    }
                    else if(opBlobIter->validParams.empty())
                    {
                        set(expLine.at(0), expLine.at(1));
                    }
                    else if(expValOpts.size() > 1)
                    {
                        for(expValOptsIter = expValOpts.begin(); expValOptsIter != expValOpts.end(); ++expValOptsIter)
                        {
                            if((*expValOptsIter) == expLine.at(1))
                                set(expLine.at(0), expLine.at(1));
                        }
                    }
                    else
                        returnValue.push_back(strToCheck);
                }
            }
        }
        else
            returnValue.push_back(strToCheck);
    }
    dprint(className + "::" + functionName, "Returning " + pwan::strings::fromInt(returnValue.size()) + " discarded elements", 3);
    return returnValue;
}

std::vector<std::string> pwan::options::checkCmdLine(int argc, char** argv)
{
    std::vector<std::string> toCheck;
    for(int i = 0; i != argc; ++i)
    {
        std::string tmpS = argv[i];
        toCheck.push_back(tmpS);
    }
    return checkCmdLine(toCheck);
}

std::vector<std::string> pwan::options::checkCmdLine(const std::vector<std::string>& args)
{
    const std::string functionName("checkCmdLine");
    typedef std::vector<std::string>::const_iterator vecStrIter;
    std::vector<optionBlob>::iterator opBlobIter;
    std::vector<std::string> returnValue, parsedOpt, valParms, lastValParms;
    vecStrIter vsIter, valParmsIter;
    std::string lastOpt;
    int i, added;
    i = added = 0;
    if(!data)
        return returnValue;

    dprint(className + "::" + functionName, "Checking a vector of " + pwan::strings::fromInt(args.size()) + " elements", 3);
    if(!args.empty())
        data->programName = args.at(0);
    for(opBlobIter = data->allowedOptions.begin(); opBlobIter != data->allowedOptions.end(); ++opBlobIter)
    {
        if(opBlobIter->validParams == "*")
        {
            data->defaultOpt = opBlobIter->longOpt;
            break;
        }
    }
    for(vsIter = args.begin() +1; vsIter != args.end(); ++vsIter)
    {
        if(!lastOpt.empty())
        {
            if(lastValParms.empty())
                set(lastOpt, (*vsIter));
            else
            {
                for(valParmsIter = lastValParms.begin(); valParmsIter != lastValParms.end(); ++valParmsIter)
                {
                    if((*valParmsIter) == (*vsIter))
                        set(lastOpt, (*vsIter));
                }
            }
            lastOpt.clear();
            lastValParms.clear();
            continue;
        }
        while(vsIter->at(i) == '-' || vsIter->at(i) == '/')
            ++i;
        parsedOpt = pwan::strings::explode(vsIter->substr(i), ":");
        for(opBlobIter = data->allowedOptions.begin(); opBlobIter != data->allowedOptions.end(); ++opBlobIter)
        {
            added = 0;
            if((opBlobIter->shortOpt == parsedOpt.at(0)) || (opBlobIter->longOpt == parsedOpt.at(0)))
            {
                valParms = pwan::strings::explode(opBlobIter->validParams, ":");
                if(opBlobIter->validParams.empty() && parsedOpt.size() == 2)
                {
                    set(opBlobIter->longOpt, parsedOpt.at(1));
                    added = 1;
                }
                else if(opBlobIter->validParams == "!")
                {
                    added = 1;
                    set(opBlobIter->longOpt, "true");
                    break;
                }
                else if(!opBlobIter->validParams.empty() && parsedOpt.size() == 2)
                {
                    if(valParms.size() == 1)
                    {
                        if(valParms.at(0) == parsedOpt.at(1))
                        {
                            added = 1;
                            set(opBlobIter->longOpt, parsedOpt.at(1));
                            break;
                        }
                    }
                    else
                    {
                        for(valParmsIter = valParms.begin(); valParmsIter != valParms.end(); ++valParmsIter)
                        {
                            if((*valParmsIter) == parsedOpt.at(1))
                            {
                                added = 1;
                                set(opBlobIter->longOpt, parsedOpt.at(1));
                                break;
                            }
                        }
                    }
                }
                else
                {
                    added = 1;
                    lastOpt = opBlobIter->longOpt;
                    lastValParms = valParms;
                    break;
                }
            }
        }
        if(added == 0)
        {
            if(!data->defaultOpt.empty() && !((*vsIter).at(0) == '-' || (*vsIter).at(0) == '/'))
            {
                lastOpt = get(data->defaultOpt);
                if(!lastOpt.empty())
                    lastOpt += " ";
                set(data->defaultOpt, lastOpt + (*vsIter));
                lastOpt.clear();
            }
            else
            {
                returnValue.push_back(*vsIter);
            }
        }
    }
    dprint(className + "::" + functionName, "Returning " + pwan::strings::fromInt(returnValue.size()) + " discarded elements", 3);
    return returnValue;
}

void pwan::options::setDataBlob(dataBlob *newData)
{
    data = newData;
}
