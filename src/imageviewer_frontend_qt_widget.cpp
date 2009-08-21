#include <QtGui/QPainter>

#include "imageviewer_frontend_qt_widget.h"
#include "imageviewer_frontend_qt_widget.moc"
#include "imageviewer_frontend_qt_new.h"

pwan::imageviewer_frontend_qt_widget::imageviewer_frontend_qt_widget(QWidget *parent): QWidget(parent)
{
    connect(this, SIGNAL(exitprogram()), this, SLOT(close()));
}

void pwan::imageviewer_frontend_qt_widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(QRect(0,0,this->geometry().width(), this->geometry().height()), QColor(0,0,0));
    painter.setPen(Qt::white);
    if(imgbuf && !imgbuf->image->isNull())
    {
        painter.drawImage(QPointF(0,0), (*imgbuf->image), QRect(0,0,this->geometry().width(), this->geometry().height()));
    }
    else
    {
        painter.drawText(this->rect(), Qt::AlignCenter, "Loading Image...");
    }
}

void pwan::imageviewer_frontend_qt_widget::keyPressEvent(QKeyEvent *keyevent)
{
    int keycodefound = keyevent->key();
    p_img_keyevent pkey = programKeys.find(keycodefound)->second;
    switch (pkey)
    {
        case QUIT:
            emit exitprogram();
            break;
        case FULLSCREEN:
            setWindowState(windowState() ^ Qt::WindowFullScreen);
            update(); 
            break;
        case NEXTIMAGE:
            emit nextimage();
            update();
        default:
            break;
    }
}

void pwan::imageviewer_frontend_qt_widget::setupKey(int whatkey, p_img_keyevent whatevent)
{
    programKeys[whatkey] = whatevent;
}

void pwan::imageviewer_frontend_qt_widget::setImage(boost::shared_ptr<pwan::imagebuffer_qt> newImg)
{
    imgbuf = newImg;
}
