#ifndef PWANUTILS_H
#define PWANUTILS_H

#include <vector>
#include <string>

namespace pwan
{
    class doubleint
    {
        public:
            int x;
            int y;
    };

    namespace html
    {
        std::vector<std::string>    getImageLinks(std::string filename);
        std::vector<std::string>    getLinks(std::string filename);
    }

    enum fileWriteMode {OverWrite, Append};

    std::string                     getextention(const std::string& filename);
    float                           calculatezoom(int imagedims[2], int displaydims[2]);
    doubleint                       calculateoffset(int imagedims[2], int displaydims[2]);

    std::string                     readFile(const std::string filename);
    std::vector<std::string>        parsebrackets(const std::string url);
    int                             writefile(const std::string filename, const char data[], const int datasize, const int writemode);
}

#endif
