#include "imageviewer_frontend_base.h"

#include <boost/bind.hpp>

pwan::imageviewer_frontend_base::~imageviewer_frontend_base(void)
{

}

pwan::p_returnValue pwan::imageviewer_frontend_base::run(void)
{
    this_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&imageviewer_frontend_base::do_work, this)));
    return P_OK;
}
