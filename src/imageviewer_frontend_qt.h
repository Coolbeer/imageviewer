#ifndef IMAGEVIEWER_FRONTEND_QT_H
#define IMAGEVIEWER_FRONTEND_QT_H

#include "imageviewer_frontend_base.h"
#include <boost/thread/thread.hpp>

namespace pwan
{
    class imageviewer_frontend_qt : public imageviewer_frontend_base
    {
        public:
            virtual void show(void);
            virtual p_returnValue run(void);
        private:
            static void intRun(void);
            boost::thread uber;
    };
}

#endif
