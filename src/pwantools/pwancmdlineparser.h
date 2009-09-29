#ifndef PWANCMDLINEPARSER_H
#define PWANCMDLINEPARSER_H

#include <string>
#include <vector>
#include <map>

#include "pwantools_enums.h"
#include "pwandebug.h"

namespace pwan
{
    enum e_clpFlag { NO_PARAMETER, ANY_PARAMETER, RESTRICTED_PARAMETER, DEFAULT_PARAMETER };

    struct optionsReturn
    {
        std::string option;
        std::string parameter;
    };
    struct optBlob
    {
        std::string                                     shortOpt;
        std::string                                     longOpt;
        std::string                                     description;
        std::string                                     validParams;
        e_clpFlag                                       flag;
    };

    class t_cmdlineParser : public pwan::debug
    {
        public:
                                                        t_cmdlineParser(void);
            void                                        setAllowedOption(const std::string &shortOpt, const std::string &longOpt, const std::string &description, const e_clpFlag &flag = NO_PARAMETER);
            p_returnValue                               setValidParameter(const std::string &longOpt, const std::string &validParams);
            std::string                                 makeHelp(void);
            p_returnValue                               checkCmdLine(const int &argc, char **argv);
            std::vector<optionsReturn>                  returnFoundOptions(void);
            p_returnValue                               get(const std::string &name, std::string &returnValue);
            p_returnValue                               set(const std::string &name, const std::string &value);
        private:
            std::vector<optionsReturn>                  setOptions;
            static std::map<std::string, std::string>   internalData;
            std::vector<optBlob>                        allowedOptions;
            int                                         defaultOpt;
            std::string                                 className;
    };
}

#endif
