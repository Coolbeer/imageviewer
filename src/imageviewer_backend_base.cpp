#include <boost/filesystem.hpp>

#include "imageviewer_backend_base.h"
#include "pwanstrings.h"
#include "string.h"

pwan::imageviewer_backend_base::~imageviewer_backend_base()
{
}

std::vector<std::string> pwan::imageviewer_backend_base::makeimagelist(std::string &path, std::vector<std::string> &imageformats)
{
    std::vector<std::string> returnValue;
    namespace fs = boost::filesystem;
    fs::path fsp = fs::system_complete(path);
    if(!fs::exists(path))
    {
        return returnValue;
    }
    if(!fs::is_directory(fsp))
    {
        fsp = fsp.remove_filename();
    }
    fs::directory_iterator dir_itr(fsp), dir_end;
    for(;dir_itr != dir_end; ++dir_itr)
    {
        for(std::vector<std::string>::iterator it = imageformats.begin(); it != imageformats.end(); ++it)
        {
            if(pwan::strings::toLower(dir_itr->path().extension()) == (*it))
            {
                if(!returnValue.empty())
                {
                    std::vector<std::string>::iterator it2;
                    for(it2 = returnValue.begin(); it2 != returnValue.end(); ++it2)
                    {
                        if(strcmp(dir_itr->string().c_str(), it2->c_str()) < 0)
                        {
                            returnValue.insert(it2, dir_itr->string());
                            break;
                        }
                    }
                    if(it2 == returnValue.end())
                        returnValue.push_back(dir_itr->string());
                }
                else
                    returnValue.push_back(dir_itr->string());
                break;
            }
        }
    }
    return returnValue;
}
