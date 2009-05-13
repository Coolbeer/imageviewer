#include "imageviewer_frontend_qt.h"

#include <iostream>
#include <unistd.h>
#include <boost/bind.hpp>

void pwan::imageviewer_frontend_qt::show(void)
{
    return;
}

void pwan::imageviewer_frontend_qt::intRun(void)
{
    while(1)
    {
        std::cout << "B";
        usleep(100000);
    }
}

pwan::p_returnValue pwan::imageviewer_frontend_qt::run(void)
{
//    uber = boost::thread(&pwan::imageviewer_frontend_qt::intRun);
    //uber = boost::thread (&intRun);
    //uber = boost::thread(&pwan::imageviewer_frontend_qt::intRun);
    return P_OK;

}
