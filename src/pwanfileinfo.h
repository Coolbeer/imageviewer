#ifndef PWANFILEINFO_H
#define PWANFILEINFO_H

#include <vector>
#include <string>

namespace pwan
{
    class fileInfo
    {
        public:
            fileInfo();
            fileInfo(const std::string& file);
            std::string fileName(void);
            std::string path(void);
            uint64_t size(void);

        private:
            void setFileName(const std::string& newFileName);
            void setPath(const std::string& newPath);
            void setSize(uint64_t newSize);

            std::string absolutePath(std::string path);

            std::string internalfilename;
            std::string internalpath;
            uint64_t internalsize;
        friend class dir;
    };
}

#endif
