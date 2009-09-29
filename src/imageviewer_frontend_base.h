#ifndef IMAGEVIEWER_FRONTEND_BASE_H
#define IMAGEVIEWER_FRONTEND_BASE_H

#include "pwantools/pwantools_enums.h"

namespace pwan
{
    class imageviewer_frontend_base
    {
        public:
            virtual                         ~imageviewer_frontend_base();
            virtual int                     startup(void) = 0;
            virtual void                    init(void) = 0;
            virtual void                    setScaled(bool onoff) = 0;
        private:
    };
}

#endif
