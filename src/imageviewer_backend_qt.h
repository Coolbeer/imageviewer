#ifndef IMAGEVIEWER_BACKEND_QT_H
#define IMAGEVIEWER_BACKEND_QT_H

#include "imageviewer_backend_base.h"

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/cstdint.hpp>

#include <string>
#include <vector>

namespace pwan
{
    class imageviewer_backend_qt : public imageviewer_backend_base
    {
        public:
                                                                    ~imageviewer_backend_qt(void);
            void                                                    start(void);
            void                                                    stop(void);
            void                                                    loadImage(std::string &filename);
            boost::shared_ptr<imagebuffer>                          getImage(std::string &filename);
        private:
            void                                                    do_work(void);
            boost::shared_ptr<boost::thread>                        m_thread;
            boost::mutex                                            m_mutex;
            std::vector<std::string>                                fileName;
            bool                                                    abort;
            boost::shared_ptr<imagebuffer>                          image1;
            boost::shared_ptr<imagebuffer>                          image2;
    };
}

#endif
