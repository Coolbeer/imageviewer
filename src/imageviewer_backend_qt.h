#ifndef IMAGEVIEWER_BACKEND_QT_H
#define IMAGEVIEWER_BACKEND_QT_H

#include "imageviewer_backend_base.h"

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>


namespace pwan
{
    class imageviewer_backend_qt : public imageviewer_backend_base
    {
        public:
            int init(void);
        private:
            void do_work(void);
            boost::shared_ptr<boost::thread> m_thread;
            boost::mutex m_mutex;
    };
}

#endif
