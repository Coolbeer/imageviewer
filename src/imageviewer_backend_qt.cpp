#include "imageviewer_backend_qt.h"

int pwan::imageviewer_backend_qt::init()
{
        assert(!m_thread);
        m_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&pwan::imageviewer_backend_qt::do_work, this)));
        return 0;
}

void pwan::imageviewer_backend_qt::do_work()
{

}
