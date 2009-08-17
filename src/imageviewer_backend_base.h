#ifndef IMAGEVIEWER_BACKEND_BASE_H
#define IMAGEVIEWER_BACKEND_BASE_H

namespace pwan
{
    class imageviewer_backend_base
    {
        public:
            virtual ~imageviewer_backend_base();
            virtual void start(void) = 0;
            virtual void stop(void) = 0;

    };
}

#endif
