#ifndef IMAGEVIEWER_BACKEND_QT_H
#define IMAGEVIEWER_BACKEND_QT_H

#include "imageviewer_backend_base.h"

#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <string>
#include <vector>

namespace pwan
{
    struct imagebuffer
    {
        std::string filename;
        QImage image;
    };

    class imageviewer_backend_qt : public imageviewer_backend_base
    {
        public:
            void                                start(void);
            void                                stop(void);
        private:
            void                                do_work(void);
            boost::shared_ptr<boost::thread>    m_thread;
            boost::mutex                        m_mutex;
            std::vector<std::string>            fileName;
            std::vector<int>                    imageslots;
            bool                                abort;
            std::vector<boost::shared_ptr<imagebuffer>>            images;

    };
}

#endif
