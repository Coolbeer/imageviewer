#include <QtCore/QTextCodec>

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
            boost::mutex::scoped_lock l(m_mutex);
            image = QImage(0,0,QImage::Format_Invalid);
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            QTextCodec::setCodecForCStrings (codec);
            image.load(QString().fromStdString(fileName.at(0)));
/*            if(image.isNull())
                emit imagePassDone(image, fileName.at(0), imageslots.at(0), -1);
            else
                emit imagePassDone(image, fileName.at(0), imageslots.at(0));
*/
            fileName.erase(fileName.begin());
            imageslots.erase(imageslots.begin());
        }
        boost::mutex::scoped_lock l(m_mutex);
        if (abort)
            break;
    }
}
