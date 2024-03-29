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
    if(imgbuf && imgbuf->image && !imgbuf->image->isNull())
    {
        QRect textbox;
        QRect text;
        QString imagefile;
        int xoffset = 0;
        int yoffset = 0;

        if(imgbuf->image->width() <= this->geometry().width())
            xoffset = (this->geometry().width()/2) - (imgbuf->image->width()/2);
        if(imgbuf->image->height() <= this->geometry().height())
            yoffset = (this->geometry().height()/2) - (imgbuf->image->height()/2);

        painter.drawImage(QPoint(xoffset,yoffset), (*imgbuf->image), QRect(0,0,imgbuf->image->width(), imgbuf->image->height()));
        painter.setPen(Qt::black);
        painter.setBrush(QColor(255, 255, 255, 190));
        imagefile = QString::fromStdString(imgbuf->filename);
        textbox = painter.boundingRect(this->rect(), Qt::AlignBottom | Qt::AlignLeft, imagefile);
        text = textbox;
        textbox.setWidth(textbox.width() + 10);
        text.setLeft(text.left() +5);
        text.setRight(text.right() +5);
        painter.drawRect(textbox);
        painter.drawText(text, Qt::AlignBottom | Qt::AlignLeft, imagefile);
    }
    else
    {
        painter.drawText(this->rect(), Qt::AlignCenter, "Loading Image...");
    }
}
std::string pwan::imageviewer_frontend_qt_widget::curImage(void)
{
    if(imgbuf && imgbuf->image)
        return imgbuf->filename;
    else
        return "";
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
            break;
        case PREVIMAGE:
            emit previmage();
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
