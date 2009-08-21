#ifndef IMAGEVIEWER_BACKEND_BASE_H
#define IMAGEVIEWER_BACKEND_BASE_H

#include <boost/shared_array.hpp>
#include <boost/cstdint.hpp>
#include <string>
#include <vector>

namespace pwan
{
    struct imagebuffer
    {
        std::string                         filename;
        boost::uint16_t                     width;
        boost::uint16_t                     height;
        boost::uint8_t                      depth;
        boost::uint32_t                     noOfBytes;
        boost::shared_array<unsigned char>  data;
    };

    class imageviewer_backend_base
    {
        public:
            virtual                         ~imageviewer_backend_base();
            virtual void                    start(void) = 0;
            virtual void                    stop(void) = 0;
            std::vector<std::string>        makeimagelist(std::string &path, std::vector<std::string> &imageformats);
    };
}

#endif
