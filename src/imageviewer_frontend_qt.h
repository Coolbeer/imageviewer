#ifndef IMAGEVIEWER_FRONTEND_QT_H
#define IMAGEVIEWER_FRONTEND_QT_H

#include <QtGui/QApplication>
#include "imageviewer_frontend_base.h"
#include "t_imageviewer.h"

namespace pwan
{
    class imageviewer_frontend_qt : public imageviewer_frontend_base
    {
        public:
            imageviewer_frontend_qt(void);
            void init(int argc, char **argv);
            int startup(void);
            int startimageviewer(std::string filename);
            void setScaled(bool onoff);
        private:
            QApplication *app;
            t_imageviewer *imageviewer;
    };
}
#endif
