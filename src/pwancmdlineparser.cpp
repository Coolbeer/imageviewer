#include "pwancmdlineparser.h"
#include "../config.h"
#include "pwanstrings.h"

#include <iostream>

pwan::t_cmdlineParser::t_cmdlineParser(void)
{
    defaultOpt = -1;
}

void pwan::t_cmdlineParser::setAllowedOption(const std::string &shortOpt, const std::string &longOpt, const std::string &description, e_clpFlag flag)
{
    optBlob newOption;
    newOption.shortOpt = shortOpt;
    newOption.longOpt = longOpt;
    newOption.description = description;
    newOption.flag = flag;
    allowedOptions.push_back(newOption);
    if(flag == DEFAULT_PARAMETER)
        defaultOpt = (int)allowedOptions.size()-1;
}

pwan::p_returnValue pwan::t_cmdlineParser::setValidParameter(const std::string &longOpt, const std::string &validParams)
{
    std::vector<optBlob>::iterator iter;
    for(iter = allowedOptions.begin(); iter != allowedOptions.end(); ++iter)
    {
        if(longOpt == iter->longOpt)
        {
            iter->validParams = validParams;
            return P_OK;
        }
    }
    return P_ERROR;
}

std::string pwan::t_cmdlineParser::makeHelp(void)
{
    std::string returnValue;
    std::vector<optBlob>::iterator opBlobIter;
    bool hasOpt = false;
    size_t longestShort = 0;
    size_t longestLong = 0;

    returnValue = "Usage: ";
    returnValue += PACKAGE_NAME;

    if((defaultOpt != 0 && allowedOptions.size() > 1) || (defaultOpt == 0 && allowedOptions.size() > 0))
    {
        returnValue += " [OPTIONS]";
        hasOpt = true;
    }
    if(defaultOpt != 0)
    {
        returnValue += " [" + allowedOptions.at(defaultOpt).longOpt + "]";
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
            if(opBlobIter->longOpt == allowedOptions.at(defaultOpt).longOpt)
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
    return returnValue;
}

pwan::p_returnValue pwan::t_cmdlineParser::checkCmdLine(int argc, char **argv)
{
    std::vector<std::string> args;
    std::vector<std::string>::iterator vecStrIter;
    optionsReturn opRetList;

    if(argc == 1)
        return P_NO_ARGUMENTS;

    for(int i = 0; i != argc; ++i)                                                  //put the argv in a vector<string>
    {
        std::string tmpS = argv[i];
        args.push_back(tmpS);
    }

    vecStrIter = args.begin()+1;
    while(vecStrIter != args.end())
    {
        if(vecStrIter->size() > 1)                                                  //Avoid a exception
        {
            if((vecStrIter->at(0) == '-' && vecStrIter->at(1) != '-') || (vecStrIter->at(0) == '-' && vecStrIter->at(1) == '-'))
            {
                for(std::vector<optBlob>::iterator optIter = allowedOptions.begin(); optIter != allowedOptions.end(); ++optIter)
                {
                    if((*vecStrIter) == "-" + optIter->shortOpt || (*vecStrIter) == "--" + optIter->longOpt)
                    {
                        if(optIter->flag == NO_PARAMETER)
                        {
                            opRetList.option = optIter->longOpt;
                            opRetList.parameter.erase();
                            setOptions.push_back(opRetList);
                            break;
                        }
                        else if(optIter->flag == ANY_PARAMETER)
                        {
                            opRetList.option = optIter->longOpt;
                            ++vecStrIter;
                            opRetList.parameter = (*vecStrIter);
                            setOptions.push_back(opRetList);
                            break;
                        }
                        else if(optIter->flag == RESTRICTED_PARAMETER)
                        {
                            bool isFound = false;
                            opRetList.option = optIter->longOpt;
                            ++vecStrIter;
                            std::vector<std::string> expValids;
                            expValids = pwan::strings::explode(optIter->validParams, ":");
                            for(std::vector<std::string>::iterator expIter = expValids.begin(); expIter != expValids.end(); ++expIter)
                            {
                                if((*expIter) == (*vecStrIter))
                                {
                                    opRetList.parameter = (*vecStrIter);
                                    isFound = true;
                                    break;
                                }
                            }
                            if(isFound)
                                setOptions.push_back(opRetList);
                            else
                                return P_ERROR;
                            break;
                        }
                        else if(optIter->flag == DEFAULT_PARAMETER)
                        {
                            opRetList.option = optIter->longOpt;
                            ++vecStrIter;
                            opRetList.parameter = (*vecStrIter);
                            setOptions.push_back(opRetList);
                            break;
                        }

                    }
                }
            }
            else if(defaultOpt != -1 && vecStrIter->at(0) != '-')
            {
                std::vector<optionsReturn>::iterator opIter = setOptions.begin();
                for(opIter = setOptions.begin(); opIter != setOptions.end(); ++opIter)
                {
                    if(opIter->option == allowedOptions.at(defaultOpt).longOpt)
                    {
                        opIter->parameter += ' ';
                        opIter->parameter += (*vecStrIter);
                        break;
                    }
                }
                if(opIter == setOptions.end())
                {
                    opRetList.option = allowedOptions.at(defaultOpt).longOpt;
                    opRetList.parameter = (*vecStrIter);
                    setOptions.push_back(opRetList);
                }

            }
        }
        ++vecStrIter;
    }
    return P_OK;
}

std::vector<pwan::optionsReturn> pwan::t_cmdlineParser::returnFoundOptions(void)
{
    return setOptions;
}
