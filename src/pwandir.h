#ifndef PWANDIR_H
#define PWANDIR_H

#include <string>
#include <vector>

#include "pwanfileinfo.h"

namespace pwan
{
    class dir
    {
        public:
            dir(const std::string& path = ".");
            std::vector<pwan::fileInfo> entryInfoList(const std::vector<std::string>& filter);

        private:
            std::string currentpath;
    };

}

#endif
