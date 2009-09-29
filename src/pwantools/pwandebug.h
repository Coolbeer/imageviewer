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
    struct t_savedMessage
    {
            std::string                             Message;
            unsigned int                            debugLevel;
    };

    class debug
    {
        public:
                                                    debug(void);
            void                                    dprint(const std::string& from, const std::string& message, unsigned int p_debugLevel = 1);
            void                                    dprint(const std::string& message);
            void                                    setDebugLevel(unsigned int debugLevel);
            int                                     getDebugLevel(void);
        private:
            std::string                             className;
            static std::vector<t_savedMessage>      savedMessages;
            static unsigned int                     debugLevel;
            unsigned int                            maxSavedLog;
    };
}
#endif
