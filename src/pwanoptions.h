#ifndef PWANOPTIONS_H
#define PWANOPTIONS_H

#include <string>
#include <list>
#include <map>
#include <vector>

namespace pwan
{
    struct optionBlob
    {
        std::string                                 shortOpt;
        std::string                                 longOpt;
        std::string                                 description;
        std::string                                 validParams;
    };

    class options
    {
        public:
                                                    options(void);
            int                                     set(const std::string& name, const std::string& value);
            std::string                             get(const std::string& name);
            std::list<std::string>                  dump(void);
            void                                    setOption(const std::string& shortOpt,                      //Optional
                                                              const std::string& longOpt,                       //Mandatory
                                                              const std::string& description,                   //Optional
                                                              const std::string& validParams);                  //Optional(empty = any parameter, ! = no parameter, * = default parameter)
            std::vector<std::string>                checkIniFile(const std::string& filename);
            std::vector<std::string>                checkCmdLine(int argc, char** argv);
            std::vector<std::string>                checkCmdLine(const std::vector<std::string>& args);
            std::string                             makeHelp(void);
        private:
            std::map<std::string, std::string>      internalData;
            std::string className;
            std::vector<optionBlob>                 allowedOptions;
            std::string                             defaultOpt;
            std::string                             programName;
    };
}

#endif
