#ifndef IMAGEVIEWER_FRONTEND_QT_WIDGET_H
#define IMAGEVIEWER_FRONTEND_QT_WIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QKeyEvent>
#include <boost/shared_ptr.hpp>
#include <map>
#include "pwantools_enums.h"

namespace pwan
{
    struct imagebuffer_qt;

    class imageviewer_frontend_qt_widget : public QWidget
    {
        Q_OBJECT

        public:
                                                                imageviewer_frontend_qt_widget(QWidget *parent = 0);
            void                                                setupKey(int, p_img_keyevent);
            void                                                setImage(boost::shared_ptr<pwan::imagebuffer_qt> newImg);
        private:
            void                                                paintEvent(QPaintEvent *);
            void                                                keyPressEvent(QKeyEvent *keyevent);
            std::map<int, p_img_keyevent>                       programKeys;
            boost::shared_ptr<pwan::imagebuffer_qt>             imgbuf;
        signals:
            void                                                exitprogram(void);
            void                                                nextimage(void);

    };
}
#endif
