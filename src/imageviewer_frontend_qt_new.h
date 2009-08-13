#ifndef IMAGEVIEWER_FRONTEND_QT_NEW_H
#define IMAGEVIEWER_FRONTEND_QT_NEW_H

#include <QtGui/QApplication>
#include "imageviewer_frontend_base.h"

namespace pwan
{
    class imageviewer_frontend_qt_new : public imageviewer_frontend_base, public QApplication
    {
        public:
            imageviewer_frontend_qt_new(int argc, char **argv);
    };
}
#endif
