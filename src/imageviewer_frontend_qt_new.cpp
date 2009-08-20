#include <QtGui/QPainter>

#include "imageviewer_frontend_qt_new.h"
#include "imageviewer_frontend_qt_new.moc"
pwan::imageviewer_frontend_qt_new::imageviewer_frontend_qt_new(int argc, char **argv, QWidget *parent): QApplication(argc, argv), QWidget(parent)
{
}

int pwan::imageviewer_frontend_qt_new::startup(void)
{
    timer = new QTimer(qApp);
    qApp->connect(timer, SIGNAL(timeout()), qApp, SLOT(processOneThing()));
    timer->start(10);
    this->show();
    return qApp->exec();
}

void pwan::imageviewer_frontend_qt_new::init(void)
{
    backend.start();
    return;
}

void pwan::imageviewer_frontend_qt_new::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(QRect(0,0,this->geometry().width(), this->geometry().height()), QColor(0,0,0));
    painter.setPen(Qt::white);
    if(!imgbuf.empty() && imgbuf.at(0))
    {
        QImage image(imgbuf.at(0)->data.get(), imgbuf.at(0)->width, imgbuf.at(0)->height, QImage::Format_ARGB32);
        painter.drawImage(QPointF(0,0), image, QRect(0,0,this->geometry().width(), this->geometry().height()));
    }
    else
    {
        painter.drawText(this->rect(), Qt::AlignCenter, "Loading Image...");
    }
}

void pwan::imageviewer_frontend_qt_new::setScaled(bool onoff)
{
    scaled = onoff;
}

int pwan::imageviewer_frontend_qt_new::setFirstImage(std::string &imagefilename)
{
    backend.loadImage(imagefilename);
    currentimage = imagefilename;
    return 1;
}

void pwan::imageviewer_frontend_qt_new::processOneThing()
{
    boost::shared_ptr<imagebuffer> tmp(backend.getImage(currentimage));
    if(tmp)
        imgbuf.push_back(tmp);
    update();

}
