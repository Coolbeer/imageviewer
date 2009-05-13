#include <iostream>
#include <dirent.h>
#include <stdlib.h>

#include "pwandir.h"
#include "pwanstrings.h"
#include "pwanutils.h"

pwan::dir::dir(const std::string& path)
{
    currentpath = path;
}

std::vector<pwan::fileInfo> pwan::dir::entryInfoList(const std::vector<std::string>& filter)
{
    bool inserted = false;
    std::vector<pwan::fileInfo> returnvalue;
    std::string ext, tmpfilename;
    DIR *dirpointer;
    struct dirent *dirinfo;

    dirpointer = opendir(currentpath.c_str());
    if(dirpointer != NULL)
    {
        while((dirinfo = readdir(dirpointer)))
        {
            tmpfilename = dirinfo->d_name;
            if(tmpfilename != ".." && tmpfilename != ".")
            {
                if(filter.size() != 0)
                {
                    ext = pwan::strings::toLower(pwan::getextention(tmpfilename));
                    for(unsigned int i = 0; i != filter.size(); ++i)
                        if(ext == filter.at(i))
                        {
                            if(returnvalue.size() != 0)
                            {
                                for(unsigned int i2 = 0; i2 != returnvalue.size(); ++i2)
                                {
                                    if(tmpfilename.compare(returnvalue.at(i2).fileName()) < 0)
                                    {
                                        //pwan::fileInfo(path + "/" + tmpfilename);
                                        returnvalue.insert(returnvalue.begin()+i2, pwan::fileInfo(currentpath+"/"+tmpfilename));
                                        inserted = true;
                                        break;
                                    }
                                }
                                if(!inserted)
                                    returnvalue.push_back(pwan::fileInfo(currentpath+"/"+tmpfilename));
                                else
                                    inserted = false;
                            }
                            else
                                returnvalue.push_back(pwan::fileInfo(currentpath+"/"+tmpfilename));
                        }
                }
                else
                    returnvalue.push_back(pwan::fileInfo(currentpath+"/"+tmpfilename));
            }
        }
        closedir(dirpointer);
    }
    else
    {
        std::cout << "could not open directory \"" << currentpath << "\"\n\n";
        exit(1);
    }
    return returnvalue;
}
