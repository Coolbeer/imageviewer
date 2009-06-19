#include <iostream>

#include "pwandebug.h"
#include "pwanstrings.h"

extern unsigned int debugLevel;

pwan::debug::debug(void)
{
    className = "debug";
    maxSavedLog = 20;
}

void pwan::debug::dprint(const std::string& from, const std::string& message, unsigned int p_debugLevel)
{
    std::string completeMessage;
    completeMessage = from + ": " + message;
    if(debugLevel >= p_debugLevel)
        dprint(completeMessage);
    else
    {
        t_savedMessage newMessage;
        newMessage.Message = completeMessage;
        newMessage.debugLevel = p_debugLevel;
        savedMessages.push_back(newMessage);
        if(savedMessages.size() > maxSavedLog)
            savedMessages.erase(savedMessages.begin());
    }
}

void pwan::debug::dprint(const std::string& message)
{
    std::cout << message << "\n";
}

void pwan::debug::setDebugLevel(unsigned int NewdebugLevel)
{
    std::string functionName("setDebugLevel");
    std::vector<t_savedMessage>::iterator iter;
    debugLevel = NewdebugLevel;
    dprint(className + "::" + functionName, "Setting debug level " + pwan::strings::fromInt(debugLevel), 3);
    dprint(className + "::" + functionName, "Printing out saved messages(if any) from lower debuglevels", 3);
    iter = savedMessages.begin();
    while(iter != savedMessages.end())
    {
        if((*iter).debugLevel <= debugLevel)
        {
            dprint((*iter).Message);
            savedMessages.erase(iter);
        }
        else
            ++iter;
    }
}

int pwan::debug::getDebugLevel(void)
{
    return debugLevel;
}
