#ifndef IMAGEVIEWER_FRONTEND_BASE_H
#define IMAGEVIEWER_FRONTEND_BASE_H

namespace pwan
{
    class imageviewer_frontend_base
    {
        public:
            virtual void show(void) = 0;
            virtual ~imageviewer_frontend_base() = 0;
        private:
    };
}

#endif
