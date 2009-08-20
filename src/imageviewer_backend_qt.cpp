#include <QtCore/QTextCodec>
#include <QtGui/QImage>
#include <boost/shared_ptr.hpp>

#ifdef _WIN32
#include "windows.h"
#endif

#include "imageviewer_backend_qt.h"

void pwan::imageviewer_backend_qt::start()
{
        assert(!m_thread);
        abort = false;
        m_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&pwan::imageviewer_backend_qt::do_work, this)));
}

void pwan::imageviewer_backend_qt::stop()
{
    assert(m_thread);
    abort = true;
    m_thread->join();
}

void pwan::imageviewer_backend_qt::do_work()
{
    while(!abort)
    {
#ifdef _WIN32
        Sleep(200);
#endif
        while(!fileName.empty())
        {
            QImage image;
            boost::shared_ptr<imagebuffer> buffer(new imagebuffer);
            boost::mutex::scoped_lock l(m_mutex);
            image = QImage(0,0,QImage::Format_Invalid);
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            QTextCodec::setCodecForCStrings (codec);
            image.load(QString().fromStdString(fileName.at(0)));
            if(!image.isNull())
            {
                buffer->filename = fileName.at(0);
                buffer->width = image.width();
                buffer->height = image.height();
                buffer->depth = image.depth();
                buffer->data.reset(new uchar[image.numBytes()]);
                memcpy(buffer->data.get(), image.bits(), image.numBytes());
                images.push_back(buffer);
            }
            fileName.erase(fileName.begin());
        }
        boost::mutex::scoped_lock l(m_mutex);
        if (abort)
            break;
    }
}

void pwan::imageviewer_backend_qt::loadImage(std::string &filename)
{
    boost::mutex::scoped_lock l(m_mutex);
    bool haveIt = false;
    for(uint i = 0; i != images.size(); ++i)
    {
        if(images.at(i)->filename == filename)
        {
            haveIt = true;
            break;
        }
    }
    if(!haveIt)
        fileName.push_back(filename);
}

boost::shared_ptr<pwan::imagebuffer> pwan::imageviewer_backend_qt::getImage(std::string &filename)
{
    boost::mutex::scoped_lock l(m_mutex);
//    bool haveIt = false;
    for(uint i = 0; i != images.size(); ++i)
    {
        if(images.at(i)->filename == filename)
        {
            return images.at(i);
        }
    }

    return boost::shared_ptr<imagebuffer>();
}