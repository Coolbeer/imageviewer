#ifndef IMAGEVIEWER_FRONTEND_BASE_H
#define IMAGEVIEWER_FRONTEND_BASE_H

#include "pwantools_enums.h"

#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>

namespace pwan
{
    class imageviewer_frontend_base
    {
        public:
            virtual ~imageviewer_frontend_base();
            virtual void show(void) = 0;
            virtual p_returnValue run(void);
        private:
            virtual void do_work(void) = 0;
            boost::shared_ptr<boost::thread> this_thread;
    };
}

#endif
