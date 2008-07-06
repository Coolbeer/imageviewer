#include <QDesktopWidget>
#include <QImageReader>
#include <QPainter>

#include "pwandir.h"
#include "pwanutils.h"

#include "t_imageviewer.moc"
#include "t_imageviewer.h"
#include "t_loadimage.h"
#include "pwanoptions.h"

extern pwan::options options;

t_imageviewer::t_imageviewer(QWidget *parent) : QWidget(parent)
{
    QDesktopWidget desk;
    QImageReader imagereader;
    QList<QByteArray> imgformats = imagereader.supportedImageFormats();
    QRect dims = desk.screenGeometry(desk.primaryScreen());
    threadloadimage = new t_loadimage;
    for (int teller = 0; teller != imgformats.size(); ++teller)
        imageformats.push_back(QString(imgformats.at(teller)).toStdString());
    zoom = 1.0;
    fullscreen = 1;
    viewerwidth = dims.width();
    viewerheight = dims.height();
    setupKeys();
    qRegisterMetaType<std::string>("std::string");
    connect(this, SIGNAL(exitprogram()), this, SLOT(close()));
    connect(threadloadimage, SIGNAL(imagePassDone(QImage, std::string, int, int)), this, SLOT(imagedone(QImage, std::string, int, int)));

    if(options.get("verbose") == "true")
    {
        std::cout << "Qt Supported Image formats:\n=================================\n";
        for(int teller = 0; teller != imgformats.size();teller++)
        {
            std::cout << qPrintable(QString(imgformats.at(teller))) << "; ";
        }
        std::cout << "\n\n";
        std::cout << "Screen Dimentions:\n=================================\n";
        std::cout << "viewerwidth = " << viewerwidth << "; viewerheight = " << viewerheight << "\n";
        std::cout << "\n";
    }
}

void t_imageviewer::setupKeys(void)
{
    nextImageKey = Qt::Key_PageDown;
    this->quitImageKey = Qt::Key_Escape;
    altQuitImageKey = Qt::Key_Return;
    prevImageKey = Qt::Key_PageUp;
    firstImageKey = Qt::Key_Home;
    lastImageKey = Qt::Key_End;
    scrollDownImageKey = Qt::Key_Down;
    scrollUpImageKey = Qt::Key_Up;
    scrollRightImageKey = Qt::Key_Right;
    scrollLeftImageKey = Qt::Key_Left;
    zoomOutImageKey = Qt::Key_9;
    zoomInImageKey = Qt::Key_0;
    toggleScaleKey = Qt::Key_8;

    altToggleScaleKey = Qt::Key_Slash;
    altPrevImageKey = 0;
    altNextImageKey = 0;
    altFirstImageKey = 0;
    altLastImageKey = 0;
    altScrollUpImageKey = 0;
    altScrollDownImageKey = 0;
    altScrollRightImageKey = 0;
    altScrollLeftImageKey = 0;
    altZoomInImageKey = Qt::Key_Plus;
    altZoomOutImageKey = Qt::Key_Minus;
}

bool t_imageviewer::startimageviewer()
{
    std::string filename = options.get("image");
    if(options.get("scale") == "true")
        scale = true;
    else
        scale = false;
    std::string path = filename.substr(0, filename.find_last_of("/"));
    if(path == filename)
        path = "";
    fileList = makeimagelist(path);
    index = fileList.end();
    for(std::vector<pwan::fileInfo>::iterator fileListIter = fileList.begin(); fileListIter != fileList.end(); ++fileListIter)
    {
        imagelist.push_back(QImage(0,0,QImage::Format_Invalid));
        imagestatuslist.push_back(0);
        if((*fileListIter).fileName() == filename.substr(filename.find_last_of("/")+1))
        {
            imageindex = fileListIter - fileList.begin();
            index = fileListIter;
        }
    }
    showFullScreen();

    if(options.get("verbose") == "true")
    {
        std::cout << "StartImageviewer\n=================================\n";
        std::cout << "filename = " << filename << "\n";
        std::cout << "path = " << path << "\n";
        std::cout << "\n";
        std::cout << "List of images:\n=================================\n";
        for (std::vector<pwan::fileInfo>::iterator fileListIter = fileList.begin(); fileListIter != fileList.end(); ++fileListIter)
            std::cout << (*fileListIter).path() << "/" << (*fileListIter).fileName() << "\n";
        std::cout << "\n";
    }

    if(index != fileList.end())
    {
        if(options.get("verbose") == "true")
        {
            std::cout << "found filename as index " << index - fileList.begin() << "; Total number of images: " << fileList.size() << "\n";
            std::cout << "\nMain Program Running\n=================================\n";
        }
        loadimage(index);
        return true;
    }
    else
    {
        if(options.get("verbose") == "true")
        {
            std::cout << "Did not find filename in filelist...\n";
            std::cout << "Quitting...\n\n";
        }
        return false;
    }
}

bool t_imageviewer::loadimage(std::vector<pwan::fileInfo>::iterator file)
{
    if(options.get("verbose") == "true")
        std::cout << "LOADIMAGE: Trying to load file: " << (*file).path() << "/" << (*file).fileName() << "\n";

    if((imagelist[file - fileList.begin()].isNull()))
    {
        threadloadimage->readimage((*file).path()+ "/" + (*file).fileName(), file - fileList.begin());
    }
    update();
    return true;
}

void t_imageviewer::paintEvent(QPaintEvent *)
{
    QString imagefile;
    QRect textbox;
    QRect text;
    int imagedims[2] = {0,0};
    int displaydims[2] = {viewerwidth, viewerheight};
    pwan::doubleint offsets;
    offsets.x = offsets.y = 0;
    QPainter painter(this);
    QImage *imagepointer = &imagelist[index - fileList.begin()];
    QString message = "Loading Image, please wait...";
    painter.fillRect(this->rect(), QColor(0,0,0));
    if(imagestatuslist.at(index - fileList.begin()) == -1)
        message = QString::fromStdString(std::string("Unable to load image " + index->fileName() + "..."));
    if(imagepointer->isNull())
    {
        painter.setPen(Qt::white);
        painter.drawText(this->rect(), Qt::AlignCenter, message);
    }
    else
    {
        imagedims[0] = imagepointer->width();
        imagedims[1] = imagepointer->height();
        if(scale)
            zoom = pwan::calculatezoom(imagedims, displaydims);
        if(zoom == 1.0)
        {
            offsets = pwan::calculateoffset(imagedims, displaydims);
            painter.drawImage(QPointF(0,0), *imagepointer, QRectF(-offsets.x,-offsets.y,viewerwidth,viewerheight));
        }
        else
        {
            imagedims[0] = ((int)(imagedims[0]*zoom));
            imagedims[1] = ((int)(imagedims[1]*zoom));
            offsets = pwan::calculateoffset(imagedims, displaydims);
            QImage imagecopy = imagepointer->scaled(imagedims[0], imagedims[1]);
            painter.drawImage(QPointF(0,0), imagecopy, QRectF(-offsets.x,-offsets.y,viewerwidth,viewerheight));
        }
        painter.setPen(Qt::black);
        painter.setBrush(QColor(255, 255, 255, 190));
        imagefile = QString::fromStdString(fileList.at(index - fileList.begin()).path() + "/" );
        imagefile += QString::fromStdString(fileList.at(index - fileList.begin()).fileName());
        textbox = painter.boundingRect(this->rect(), Qt::AlignBottom | Qt::AlignLeft, imagefile);
        text = textbox;
        textbox.setWidth(textbox.width() + 10);
        text.setLeft(text.left() +5);
        text.setRight(text.right() +5);
        painter.drawRect(textbox);
        painter.drawText(text, Qt::AlignBottom | Qt::AlignLeft, imagefile);
    }
}

std::vector<pwan::fileInfo> t_imageviewer::makeimagelist(std::string path)
{
    if(path == "")
        path = "./";
    pwan::dir pwandir(path);
    pwan::fileinfovector filelistings = pwandir.entryInfoList(imageformats);
    return filelistings;
}

void t_imageviewer::imagedone(QImage finishedimage, std::string filename, int imageslot, int imagestatus)
{
    if(options.get("verbose") == "true" && imagestatus != -1)
        std::cout << "Finished loading image: " << filename << "\n";
    else if (options.get("verbose") == "true" && imagestatus == -1)
        std::cout << "Error loading image: " << filename << "\n";
    imagelist[imageslot] = finishedimage;
    imagestatuslist[imageslot] = imagestatus;
    update();
}

void t_imageviewer::keyPressEvent(QKeyEvent *keyevent)
{
    int keycodefound = keyevent->key();

    if(keycodefound == nextImageKey || keycodefound == altNextImageKey)
    {
        if(index+1 != fileList.end())
        {
            ++index;
            threadloadimage->abortload();
            if((index-1) != fileList.begin())
                imagelist[(index-2) - fileList.begin()] = QImage(0,0,QImage::Format_Invalid);
            loadimage(index);
            if((index+1) != fileList.end())
                loadimage(index+1);
        }
        return;
    }
    else if(keycodefound == quitImageKey || keycodefound == altQuitImageKey)
    {
        emit exitprogram();
        return;
    }
    else if(keycodefound == prevImageKey || keycodefound == altPrevImageKey)
    {
        if(index != fileList.begin())
        {
            --index;
            threadloadimage->abortload();
            if((index+2) != fileList.end())
                imagelist[(index+2) - fileList.begin()] = QImage(0,0,QImage::Format_Invalid);
            loadimage(index);
            if(index != fileList.begin())
                loadimage(index-1);
        }
        return;
    }
    else if (keycodefound == firstImageKey || keycodefound == altFirstImageKey)
    {
        if(index != (fileList.begin()))
        {
            imagelist[(index -1) -fileList.begin()] = QImage(0,0,QImage::Format_Invalid);
            imagelist[(index) - fileList.begin()] = QImage(0,0,QImage::Format_Invalid);
            if((index+1) != fileList.end())
                imagelist[(index +1) - fileList.begin()] = QImage(0,0,QImage::Format_Invalid);
            index = (fileList.begin());
            threadloadimage->abortload();
            loadimage(index);
            loadimage(index+1);
        }
        return;
    }
    else if(keycodefound == lastImageKey || keycodefound == altLastImageKey)
    {
        if(index != (fileList.end()-1))
        {
            if(index != fileList.begin())
                imagelist[(index -1) -fileList.begin()] = QImage(0,0,QImage::Format_Invalid);
            imagelist[(index) - fileList.begin()] = QImage(0,0,QImage::Format_Invalid);
            if((index+1) != fileList.end())
                imagelist[(index +1) - fileList.begin()] = QImage(0,0,QImage::Format_Invalid);
            index = (fileList.end()-1);
            threadloadimage->abortload();
            loadimage(index);
            if(index != fileList.begin())
                loadimage(index-1);
        }
        return;
    }
/*  else if (keycodefound == scrollDownImageKey || keycodefound == altScrollDownImageKey)
    {
        if(keyboardoffset.y <= 0)
        {
            keyboardoffset.y -= imagesize.y()/10;
            if(offsety < (viewerheight - imagesize.y()))
                offsety = viewerheight - imagesize.y();
            update();
        }
        return;
    }
    else if (keycodefound == scrollUpImageKey || keycodefound == altScrollUpImageKey)
    {
        if(offsety <= 0)
        {
            offsety += imagesize.y()/10;
            if(offsety > 0)
                offsety = 0;
            update();
        }
        return;
    }
    else if (keycodefound == scrollRightImageKey || keycodefound == altScrollRightImageKey)
    {
        if(offsetx <= 0)
        {
            offsetx -= imagesize.x()/10;
            if(offsetx < (viewerwidth - imagesize.x()))
                offsetx = viewerwidth - imagesize.x();
            update();
        }
        return;
    }
    else if (keycodefound == scrollLeftImageKey || keycodefound == altScrollLeftImageKey)
    {
        if(offsetx <= 0)
        {
            offsetx += imagesize.x()/10;
            if(offsetx > 0)
                offsetx = 0;
            update();
        }
        return;
    }*/
    else if (keycodefound == zoomOutImageKey || keycodefound == altZoomOutImageKey)
    {
        if(zoom > 0.05)
        {
            zoom -= 0.04;
//          calculateoffset();
        }
        update();
        return;
    }
    else if (keycodefound == zoomInImageKey || keycodefound == altZoomInImageKey)
    {
        if(zoom < 3.00)
        {
            zoom += 0.04;
//          calculateoffset();
        }
        update();
        return;
    }
    else if (keycodefound == toggleScaleKey || keycodefound == altToggleScaleKey)
    {
        scale = !scale;
        zoom = 1;
        update();
        return;
    }
    else
    {
        keyevent->ignore();
        return;
    }
}
