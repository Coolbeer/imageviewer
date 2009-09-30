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
    timer->start(200);

    connect(timer, SIGNAL(timeout()), this, SLOT(processOneThing()));
    connect(myWidget.get(), SIGNAL(nextimage()), this, SLOT(nextimage()));
    connect(myWidget.get(), SIGNAL(previmage()), this, SLOT(previmage()));

    myWidget->resize(800,600);
    myWidget->move(100,100);
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
    std::vector<std::string> imagelist;
    bool haveIt = false;
    QList<QByteArray> imgformats = imagereader.supportedImageFormats();
    for (int teller = 0; teller != imgformats.size(); ++teller)
        imageformats.push_back("." + QString(imgformats.at(teller)).toStdString());

    imagelist = backend.makeimagelist(imagefilename, imageformats);
    for(unsigned int i = 0; i != imagelist.size(); ++i)
    {
        boost::shared_ptr<imagebuffer_qt> buf1(new imagebuffer_qt);
        buf1->filename = imagelist.at(i);
        images.push_back(buf1);
        if(imagefilename == imagelist.at(i))
        {
            imageindex = i;
            haveIt = true;
            backend.loadImage(imagefilename);
            if(i < imagelist.size()-1)
                backend.loadImage(imagelist.at(i+1));
            break;
        }
    }
    if(haveIt)
        return 1;
    else
        return 0;
    return 0;
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
    if(images.at(imageindex)->filename != myWidget->curImage())
    {
        myWidget->setImage(images.at(imageindex));
        if(!images.at(imageindex)->image)
        {
            boost::shared_ptr<imagebuffer> tmp(backend.getImage(images.at(imageindex)->filename));
            if(tmp)
            {
                images.at(imageindex)->image = boost::shared_ptr<QImage>(new QImage(tmp->width, tmp->height, QImage::Format_ARGB32));
                memcpy(images.at(imageindex)->image->bits(), tmp->data.get(), tmp->noOfBytes);
                myWidget->setImage(images.at(imageindex));
                myWidget->update();
            }
        }
    }
//    myWidget->update();
}

void pwan::imageviewer_frontend_qt_new::nextimage()
{
    if(imageindex < images.size()-1)
    {
        ++imageindex;
        myWidget->setImage(images.at(imageindex));
    }
    myWidget->update();
}

void pwan::imageviewer_frontend_qt_new::previmage()
{
    if(imageindex != 0)
    {
        --imageindex;
        myWidget->setImage(images.at(imageindex));
    }
    myWidget->update();
}
