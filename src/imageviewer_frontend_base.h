#ifndef IMAGEVIEWER_FRONTEND_BASE_H
#define IMAGEVIEWER_FRONTEND_BASE_H

#include "pwantools_enums.h"

namespace pwan
{
    class imageviewer_frontend_base
    {
        public:
            virtual ~imageviewer_frontend_base();
            virtual void init(int argc, char **argv) = 0;
            virtual int startup(void) = 0;
        private:
    };
}

#endif
