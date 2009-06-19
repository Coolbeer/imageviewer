#include "imageviewer_frontend_qt.h"

pwan::imageviewer_frontend_qt::imageviewer_frontend_qt(void)
{

}

void pwan::imageviewer_frontend_qt::init(int argc, char **argv)
{
    app = new QApplication(argc, argv);
    imageviewer = new t_imageviewer;
}

int pwan::imageviewer_frontend_qt::startup(void)
{
    imageviewer->show();
    return app->exec();
}

int pwan::imageviewer_frontend_qt::startimageviewer(std::string filename)
{
    return imageviewer->startimageviewer(filename);  
}

void pwan::imageviewer_frontend_qt::setScaled(bool onoff)
{
    imageviewer->setScaled(onoff);
}