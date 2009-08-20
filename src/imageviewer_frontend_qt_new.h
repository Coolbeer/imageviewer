#ifndef IMAGEVIEWER_FRONTEND_QT_NEW_H
#define IMAGEVIEWER_FRONTEND_QT_NEW_H

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtCore/QTimer>


#include "imageviewer_frontend_base.h"
#include "imageviewer_backend_qt.h"

namespace pwan
{
    class imageviewer_frontend_qt_new : public QApplication, public QWidget, public imageviewer_frontend_base
    {
        Q_OBJECT
        public:
                                                                imageviewer_frontend_qt_new(int argc, char **argv, QWidget *parent = 0);
            int                                                 startup(void);
            void                                                init(void);
            void                                                setScaled(bool onoff);
            int                                                 setFirstImage(std::string &imagefilename);
        private:
            void                                                paintEvent(QPaintEvent *);
            pwan::imageviewer_backend_qt                        backend;
            QTimer                                              *timer;
            std::vector<boost::shared_ptr<pwan::imagebuffer>>   imgbuf;
            std::string                                         currentimage;

        private slots:
            void                                                processOneThing();

    };
}

#endif
