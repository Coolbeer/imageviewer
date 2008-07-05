#include "../config.h"
#include <QApplication>
#include "main.h"
#include "t_imageviewer.h"
#include "pwandebug.h"

pwan::options options;
pwan::debug debug;

void setOptions(void);

int main (int argc, char *argv[])
{
    std::vector<std::string> args;
    for(int teller = 0; teller != argc; ++teller)
        args.push_back(std::string(argv[teller]));

    QApplication app(argc, argv);
    setOptions();
    options.checkCmdLine(argc, argv);
    if(options.get("debug") == "true")
        debug.setDebugLevel(3);
    if(options.get("verbose") == "true")
    {
        std::cout << PACKAGE_NAME << " v" << PACKAGE_VERSION << "\n\n";
        std::cout << "Raw Commandline:\n=================================\n";
        for(unsigned int teller = 0; teller != args.size(); ++teller)
            std::cout << "argc = " << teller << "; " << args.at(teller).c_str() << "\n";
        std::cout << "\n";

        std::cout << "Commandline Arguments parsed:\n=================================\n";
        std::list<std::string> hepp = options.dump();
        std::list<std::string>::iterator mapiter = hepp.begin();
        while(mapiter != hepp.end())
        {
            std::cout << (*mapiter);
            ++mapiter;
            std::cout << " : " << (*mapiter) << "\n";
            ++mapiter;
        }
        std::cout << "\n";
    }

    t_imageviewer *imageviewer = new t_imageviewer;
    if(options.get("version") == "true")
    {
        std::cout << PACKAGE_NAME << " v" << PACKAGE_VERSION << "\n\n";
        exit(0);
    }
    else if(options.get("help") == "true")
    {
        std::cout << options.makeHelp();
        exit(0);
    }
    if(options.get("image") != "")
    {
        if(!imageviewer->startimageviewer())
        {
            std::cout << "Could not load specified file...\n";
            exit(1);
        }
        imageviewer->show();
        return app.exec();
    }
    else
    {
        std::cout << PACKAGE_NAME << " v" << PACKAGE_VERSION << "\n";
        std::cout << "Missing option\nUsage: " << PACKAGE_NAME << " [OPTION]\n\n" \
                  << "Try: `" << PACKAGE_NAME << " --help` for more options.\n\n";
        exit(0);
    }
}

void setOptions(void)
{
    options.setOption("v", "verbose", "Verbose output", "!");
    options.setOption("h", "help", "This helptext", "!");
    options.setOption("V", "version", "Prints versionstring", "!");
    options.setOption("d", "debug", "Be extra verbose on output", "!");
    options.setOption("s", "scale", "Auto scale the image to fit the screen", "!");
    options.setOption("i", "image", "Specifies the image you want to load", "*");
}
