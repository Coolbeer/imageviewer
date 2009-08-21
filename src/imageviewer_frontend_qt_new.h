#ifndef IMAGEVIEWER_FRONTEND_QT_NEW_H
#define IMAGEVIEWER_FRONTEND_QT_NEW_H

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtCore/QTimer>

#include "imageviewer_frontend_base.h"
#include "imageviewer_backend_qt.h"

namespace pwan
{
    class imageviewer_frontend_qt_widget;

    struct imagebuffer_qt
    {
        std::string                         filename;
        boost::shared_ptr<QImage>           image;
    };

    class imageviewer_frontend_qt_new : public QApplication, public imageviewer_frontend_base
    {
        Q_OBJECT

        public:
                                                                        imageviewer_frontend_qt_new(int argc, char **argv);
            int                                                         startup(void);
            void                                                        init(void);
            void                                                        setScaled(bool onoff);
            int                                                         setFirstImage(std::string &imagefilename);
        private:
            void                                                        setupKeys(void);
            pwan::imageviewer_backend_qt                                backend;
            boost::shared_ptr<pwan::imageviewer_frontend_qt_widget>     myWidget;
            std::vector<boost::shared_ptr<pwan::imagebuffer_qt> >       images;
            std::vector<std::string>                                    imagelist;
            QTimer                                                      *timer;
            bool                                                        scaled;
            unsigned int                                                imageindex;
        private slots:
            void                                                        processOneThing(void);
        public slots:
            void                                                        nextimage(void);
        signals:
            void                                                        exitprogram(void);
    };
}

#endif
