#include "imageviewer_frontend_qt.h"

pwan::imageviewer_frontend_qt::imageviewer_frontend_qt(int argc, char **argv): QApplication(argc, argv)
{
}

void pwan::imageviewer_frontend_qt::init(void)
{
    imageviewer = new t_imageviewer;
}

int pwan::imageviewer_frontend_qt::startup(void)
{
    imageviewer->show();
    return qApp->exec();
}

int pwan::imageviewer_frontend_qt::setFirstImage(std::string filename)
{
    return imageviewer->startimageviewer(filename);  
}

void pwan::imageviewer_frontend_qt::setScaled(bool onoff)
{
    imageviewer->setScaled(onoff);
}