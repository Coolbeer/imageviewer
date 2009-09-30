#include <QtCore/QTextCodec>
#include <QtGui/QImage>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "imageviewer_backend_qt.h"

pwan::imageviewer_backend_qt::~imageviewer_backend_qt()
{
    stop();
}

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
        while(!fileName.empty())
        {
            QImage image;
            boost::shared_ptr<imagebuffer> buffer(new imagebuffer);
            image = QImage(0,0,QImage::Format_Invalid);
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            QTextCodec::setCodecForCStrings (codec);

            m_mutex.lock();
            image.load(QString().fromStdString(fileName.at(0)));
            m_mutex.unlock();
            if(!image.isNull())
            {
                buffer->filename = fileName.at(0);
                buffer->width = image.width();
                buffer->height = image.height();
                buffer->depth = image.depth();
                buffer->data.reset(new uchar[image.numBytes()]);
                buffer->noOfBytes = image.numBytes();
                m_mutex.lock();
                memcpy(buffer->data.get(), image.bits(), image.numBytes());
                image2 = image1;
                image1 = buffer;
                m_mutex.unlock();
            }
            m_mutex.lock();
            fileName.erase(fileName.begin());
            m_mutex.unlock();
        }
        m_mutex.lock();
        if (abort)
            break;
        m_mutex.unlock();
        boost::asio::io_service io;
        boost::asio::deadline_timer t(io, boost::posix_time::millisec(20));
        t.wait();
    }
}

void pwan::imageviewer_backend_qt::loadImage(std::string &filename)
{
    boost::mutex::scoped_lock l(m_mutex);
    bool haveIt = false;
    if(image1)
        if(image1->filename == filename)
            haveIt = true;
    if(image2 && haveIt == false)
        if(image2->filename == filename)
            haveIt = true;
    if(!haveIt)
        fileName.push_back(filename);
}

boost::shared_ptr<pwan::imagebuffer> pwan::imageviewer_backend_qt::getImage(std::string &filename)
{
    boost::mutex::scoped_lock l(m_mutex);
    if(image1)
        if(image1->filename == filename)
            return image1;
    if(image2)
        if(image2->filename == filename)
            return image2;
    fileName.push_back(filename);
    return boost::shared_ptr<imagebuffer>();
}
