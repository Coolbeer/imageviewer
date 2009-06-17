#include "imageviewer_frontend_qt.h"

#include <iostream>
#ifdef linux
#include <unistd.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif
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
#ifdef linux
        usleep(100000);
#endif
#ifdef _WIN32
        Sleep(1000000);
#endif
    }
}

pwan::p_returnValue pwan::imageviewer_frontend_qt::run(void)
{
//    uber = boost::thread(&pwan::imageviewer_frontend_qt::intRun);
    //uber = boost::thread (&intRun);
    //uber = boost::thread(&pwan::imageviewer_frontend_qt::intRun);
    return P_OK;

}
