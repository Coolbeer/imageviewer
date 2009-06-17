#include <stdexcept>
#include <fstream>
#include "pwanoptions.h"
#include "pwandebug.h"
#include "pwanstrings.h"

extern pwan::debug debug;

pwan::options::options(void)
{
    className = "pwan::options";
}

int pwan::options::set(const std::string& name, const std::string& value)
{
    std::string functionName = "set";
    ::debug.print(className + "::" + functionName, name + " = " + value, 3);
    internalData[name] = value;
    return 0;
}

std::string pwan::options::get(const std::string& name)
{
    std::string functionName = "get";
    ::debug.print(className + "::" + functionName, "name = " + name, 3);
    if(internalData.find(name) != internalData.end())
    {
        ::debug.print(className + "::" + functionName, "Returning: " + (*(internalData.find(name))).second, 3);
        return (*(internalData.find(name))).second;
    }
    else
    {
        ::debug.print(className + "::" + functionName, "Returning empty string(option not found) " , 3);
        return "";
    }
}

std::list<std::string> pwan::options::dump(void)
{
    std::string functionName = "dump";
    ::debug.print(className + "::" + functionName, "Dumping options", 3);
    std::list<std::string> returnvalue;
    for(std::map<std::string, std::string>::iterator iter = internalData.begin(); iter != internalData.end(); ++iter)
    {
        returnvalue.push_back((*iter).first);
        returnvalue.push_back((*iter).second);
    }
    return returnvalue;
}

void pwan::options::setOption(const std::string& shortOpt, const std::string& longOpt, const std::string& description, const std::string& validParams)
{
    const std::string functionName("setOption");
    optionBlob newOption;
    ::debug.print(className + "::" + functionName, "shortOpt = \"" + shortOpt + "\", longOpt = \"" + longOpt + "\"", 3);
    newOption.shortOpt = shortOpt;
    if(longOpt.empty())
        throw std::invalid_argument("no long option specified");
    newOption.longOpt = longOpt;
    newOption.description = description;
    newOption.validParams = validParams;
    allowedOptions.push_back(newOption);
}

std::string pwan::options::makeHelp(void)
{
    const std::string functionName("makeHelp");
    std::string returnValue;
    std::vector<optionBlob>::iterator opBlobIter;
    bool hasOpt = false;
    size_t longestShort = 0;
    size_t longestLong = 0;

    returnValue = "Usage: ";
    if(!programName.empty())
        returnValue += programName;
    else
        returnValue += "programName";
    if((defaultOpt != "" && allowedOptions.size() > 1) || (defaultOpt == "" && allowedOptions.size() > 0))
    {
        returnValue += " [OPTIONS]";
        hasOpt = true;
    }
    if(defaultOpt != "")
    {
        returnValue += " [" + defaultOpt + "]";
    }
    if(hasOpt)
    {
        returnValue += "\n\nWhere [OPTIONS] is one of the following:\n";
        for(opBlobIter = allowedOptions.begin(); opBlobIter != allowedOptions.end(); ++opBlobIter)
        {
            if(opBlobIter->shortOpt.size() > longestShort)
                longestShort = opBlobIter->shortOpt.size();
            if(opBlobIter->longOpt.size() > longestLong)
                longestLong = opBlobIter->longOpt.size();
        }
        for(opBlobIter = allowedOptions.begin(); opBlobIter != allowedOptions.end(); ++opBlobIter)
        {
            if(opBlobIter->longOpt == defaultOpt)
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
    ::debug.print(className + "::" + functionName, "Returning a string of " + pwan::strings::fromInt(returnValue.size()) + " bytes", 3);
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

    ::debug.print(className + "::" + functionName, "Filename = \"" + filename + "\"", 3);
    std::fstream inputFile(filename.c_str(), std::ios::in);
    if(!inputFile.is_open())
    {
        ::debug.print(className + "::" + functionName, "Failed to open inifile", 3);
        return returnValue;
    }
    while(std::getline(inputFile, strToCheck))
    {
        if(strToCheck.empty() || strToCheck[0] == '#')
            continue;
        expLine = pwan::strings::explode(strToCheck, "=");
        if(expLine.size() == 2)
        {
            for(opBlobIter = allowedOptions.begin(); opBlobIter != allowedOptions.end(); ++opBlobIter)
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
    ::debug.print(className + "::" + functionName, "Returning " + pwan::strings::fromInt(returnValue.size()) + " discarded elements", 3);
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

    ::debug.print(className + "::" + functionName, "Checking a vector of " + pwan::strings::fromInt(args.size()) + " elements", 3);
    if(!args.empty())
        programName = args.at(0);
    for(opBlobIter = allowedOptions.begin(); opBlobIter != allowedOptions.end(); ++opBlobIter)
    {
        if(opBlobIter->validParams == "*")
        {
            defaultOpt = opBlobIter->longOpt;
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
        for(opBlobIter = allowedOptions.begin(); opBlobIter != allowedOptions.end(); ++opBlobIter)
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
            if(!defaultOpt.empty() && !((*vsIter).at(0) == '-' || (*vsIter).at(0) == '/'))
            {
                lastOpt = get(defaultOpt);
                if(!lastOpt.empty())
                    lastOpt += " ";
                set(defaultOpt, lastOpt + (*vsIter));
                lastOpt.clear();
            }
            else
            {
                returnValue.push_back(*vsIter);
            }
        }
    }
    ::debug.print(className + "::" + functionName, "Returning " + pwan::strings::fromInt(returnValue.size()) + " discarded elements", 3);
    return returnValue;
}
