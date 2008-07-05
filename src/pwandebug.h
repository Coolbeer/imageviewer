#ifndef PWANDEBUG_H
#define PWANDEBUG_H

#include <string>
#include <vector>

/*
    Debuglevels:
        1  -  Normal output for user
        2  -  Normal verbose
        3  -  Very verbose(currently used for debugging)
        4  -  The extreme verbose debugging(lots of spam)
*/

namespace pwan
{
    class t_savedMessage
    {
        public:
            std::string Message;
            int debugLevel;
    };
    class debug
    {
        public:
            debug(void);
            void print(const std::string& from, const std::string& message, int debugLevel = 1);
            void print(const std::string& message);
            void setDebugLevel(int debugLevel);
            int getDebugLevel(void);

        private:
            std::string className;
            int curDebugLevel;
            std::vector<t_savedMessage> savedMessages;
            unsigned int maxSavedLog;
    };
}
#endif
