#include <QtGui/QPainter>
#include <QtGui/QImageReader>

#include "imageviewer_frontend_qt_new.h"
#include "imageviewer_frontend_qt_new.moc"
#include "imageviewer_frontend_qt_widget.h"

pwan::imageviewer_frontend_qt_new::imageviewer_frontend_qt_new(int argc, char **argv): QApplication(argc, argv)
{
    myWidget = boost::shared_ptr<pwan::imageviewer_frontend_qt_widget>(new imageviewer_frontend_qt_widget());
}

int pwan::imageviewer_frontend_qt_new::startup(void)
{
    timer = new QTimer(qApp);
    QObject::connect(timer, SIGNAL(timeout()), qApp, SLOT(processOneThing()));
    timer->start(10);
    myWidget->show();
    return qApp->exec();
}

void pwan::imageviewer_frontend_qt_new::init(void)
{
    backend.start();
    setupKeys();
    return;
}

void pwan::imageviewer_frontend_qt_new::setScaled(bool onoff)
{
    scaled = onoff;
}

int pwan::imageviewer_frontend_qt_new::setFirstImage(std::string &imagefilename)
{
    QImageReader imagereader;
    std::vector<std::string> imageformats;
    QList<QByteArray> imgformats = imagereader.supportedImageFormats();
    for (int teller = 0; teller != imgformats.size(); ++teller)
        imageformats.push_back("." + QString(imgformats.at(teller)).toStdString());

    backend.makeimagelist(imagefilename, imageformats);
    backend.loadImage(imagefilename);
    currentimage = imagefilename;
    return 1;
}

void pwan::imageviewer_frontend_qt_new::setupKeys()
{
    myWidget->setupKey(Qt::Key_PageDown, NEXTIMAGE);
    myWidget->setupKey(Qt::Key_PageUp,   PREVIMAGE);
    myWidget->setupKey(Qt::Key_Home,     FIRSTIMAGE);
    myWidget->setupKey(Qt::Key_End,      LASTIMAGE);
    myWidget->setupKey(Qt::Key_Escape,   QUIT);
    myWidget->setupKey(Qt::Key_Return,   QUIT);
    myWidget->setupKey(Qt::Key_Q,        QUIT);
    myWidget->setupKey(Qt::Key_Down,     SCROLLDOWN);
    myWidget->setupKey(Qt::Key_Up,       SCROLLUP);
    myWidget->setupKey(Qt::Key_Left,     SCROLLLEFT);
    myWidget->setupKey(Qt::Key_Right,    SCROLLRIGHT);
    myWidget->setupKey(Qt::Key_0,        ZOOMIN);
    myWidget->setupKey(Qt::Key_9,        ZOOMOUT);
    myWidget->setupKey(Qt::Key_F,        FULLSCREEN);
    myWidget->setupKey(Qt::Key_8,        SCALE);
}

void pwan::imageviewer_frontend_qt_new::processOneThing()
{
    for(unsigned int i = 0; i != images.size(); ++i)
    {
        if(currentimage == images.at(i)->filename)
            return;
    }
    boost::shared_ptr<imagebuffer> tmp(backend.getImage(currentimage));
    if(tmp)
    {
        boost::shared_ptr<imagebuffer_qt> image(new imagebuffer_qt);
        image->image = boost::shared_ptr<QImage>(new QImage(tmp->width, tmp->height, QImage::Format_ARGB32));
        memcpy(image->image->bits(), tmp->data.get(), tmp->noOfBytes);
        image->filename = tmp->filename;
        images.push_back(image);
        myWidget->setImage(image);
        myWidget->update();
    }
}
