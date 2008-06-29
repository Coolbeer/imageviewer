#ifndef PWANOPTIONS_H
#define PWANOPTIONS_H

#include <string>
#include <list>
#include <map>

namespace pwan
{
    class options
    {
        public:
                                                    options(void);
            int                                     set(std::string name, std::string value);
            std::string                             get(std::string name);
            std::list<std::string>                  dump(void);

        private:
            std::map<std::string, std::string>      internalData;
            std::string className;
    };
}

#endif
