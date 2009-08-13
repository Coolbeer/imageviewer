#ifndef IMAGEVIEWER_FRONTEND_QT_NEW_H
#define IMAGEVIEWER_FRONTEND_QT_NEW_H

#include <QtGui/QApplication>
#include <QtGui/QWidget>

#include "imageviewer_frontend_base.h"

namespace pwan
{
    class imageviewer_frontend_qt_new : public imageviewer_frontend_base, public QApplication, public QWidget
    {
        public:
                        imageviewer_frontend_qt_new(int argc, char **argv, QWidget *parent = 0);
            int         startup(void);
            void        init(void);
            void        setScaled(bool onoff);
            int         startimageviewer(std::string imagefilename);
        private:
            void paintEvent(QPaintEvent *);
    };
}
#endif
