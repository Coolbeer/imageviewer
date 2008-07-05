#include "../config.h"
#include <QApplication>
#include "main.h"
#include "t_imageviewer.h"
#include "pwandebug.h"

pwan::options options;
pwan::debug debug;

int parsecommands(int argc, char *argv[]);
void showhelp(void);

int main (int argc, char *argv[])
{
    std::vector<std::string> args;
    for(int teller = 0; teller != argc; ++teller)
        args.push_back(std::string(argv[teller]));

    QApplication app(argc, argv);
    parsecommands(argc, argv);

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
    if(options.get("request") == "version")
    {
        std::cout << PACKAGE_NAME << " v" << PACKAGE_VERSION << "\n\n";
        exit(0);
    }
    else if(options.get("request") == "help")
    {
        showhelp();
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

int parsecommands(int argc, char *argv[])
{
    std::list<std::string> arguments;
    std::list<std::string>::iterator iter;

    for (int i = 1; i != argc; i++)
        arguments.push_back(argv[i]);

    for(iter = arguments.begin(); iter != arguments.end(); ++iter)
    {
        if((*iter) == "--image" || (*iter) == "-i")
        {
            ++iter;
            if(iter != arguments.end())
            {
                options.set("image", *iter);
            }
            else
                --iter;
        }
        else if((*iter) == "--scale" || (*iter) == "-s")
        {
            options.set("scale", "true");
        }
        else if((*iter) == "--version" || (*iter) == "-V")
        {
            options.set("request", "version");
        }
        else if((*iter) == "--help" || (*iter) == "-h")
        {
            options.set("request", "help");
        }
        else if((*iter) == "--verbose" || (*iter) == "-v")
        {
            options.set("verbose", "true");
        }
    }
    return 0;
}

void showhelp(void)
{
    std::cout << PACKAGE_NAME << " v" << PACKAGE_VERSION << "\n" \
    << "Usage: " << PACKAGE_NAME << " [OPTION]\n\n" \
    << "Where [OPTION] is one of the following:\n" \
    << "-i,   --image (filename)        Specifies the image you want to load\n" \
    << "-s,   --scale                   Scales the image to fit the screen\n" \
    << "-V,   --version                 Prints versionstring\n" \
    << "-h,   --help                    This helptext\n" \
    << "-v    --verbose                 Verbose output\n" \
    << "\n";
}
