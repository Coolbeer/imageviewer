#include <iostream>

#include "pwandebug.h"
#include "pwanstrings.h"

pwan::debug::debug(void)
{
    className = "debug";
    curDebugLevel = 1;
    maxSavedLog = 20;
}

void pwan::debug::print(const std::string& from, const std::string& message, int debugLevel)
{
    std::string completeMessage;
    completeMessage = from + ": " + message;
    if(curDebugLevel >= debugLevel)
        print(completeMessage);
    else
    {
        t_savedMessage newMessage;
        newMessage.Message = completeMessage;
        newMessage.debugLevel = debugLevel;
        savedMessages.push_back(newMessage);
        if(savedMessages.size() > maxSavedLog)
            savedMessages.erase(savedMessages.begin());
    }
}

void pwan::debug::print(const std::string& message)
{
    std::cout << message << "\n";
}

void pwan::debug::setDebugLevel(int debugLevel)
{
    std::string functionName("setDebugLevel");
    std::vector<t_savedMessage>::iterator iter;
    curDebugLevel = debugLevel;
    print(className + "::" + functionName, "Setting debug level " + pwan::strings::fromInt(debugLevel), 3);
    print(className + "::" + functionName, "Printing out saved messages(if any) from lower debuglevels", 3);
    iter = savedMessages.begin();
    while(iter != savedMessages.end())
    {
        if((*iter).debugLevel <= curDebugLevel)
        {
            print((*iter).Message);
            savedMessages.erase(iter);
        }
        else
            ++iter;
    }
}

int pwan::debug::getDebugLevel(void)
{
    return curDebugLevel;
}
