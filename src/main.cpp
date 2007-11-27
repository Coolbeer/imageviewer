#include "../config.h"
#include <QApplication>
#include "main.h"
#include "t_imageviewer.h"

std::map<std::string, std::string> arguments;

std::map<std::string, std::string> parsecommands(int argc, char *argv[]);
void showhelp(void);

int main (int argc, char *argv[])
{
    std::vector<std::string> args;
    for(int teller = 0; teller != argc; ++teller)
        args.push_back(std::string(argv[teller]));

    QApplication app(argc, argv);
    arguments = parsecommands(argc, argv);

    if(arguments.find("verbose") != arguments.end())
    {
        std::cout << PACKAGE_NAME << " v" << PACKAGE_VERSION << "\n\n";
        std::cout << "Raw Commandline:\n=================================\n";
        for(unsigned int teller = 0; teller != args.size(); ++teller)
            std::cout << "argc = " << teller << "; " << args.at(teller).c_str() << "\n";
        std::cout << "\n";

        std::cout << "Commandline Arguments parsed:\n=================================\n";
        std::map<std::string, std::string>::iterator mapiter = arguments.begin();
        while(mapiter != arguments.end())
        {
            std::cout << (*mapiter).first << " : " << (*mapiter).second << "\n";
            ++mapiter;
        }
        std::cout << "\n";
    }

    t_imageviewer *imageviewer = new t_imageviewer;
    if(arguments.find("version") != arguments.end())
    {
        std::cout << PACKAGE_NAME << " v" << PACKAGE_VERSION << "\n\n";
        exit(0);
    }
    if(arguments.find("help") != arguments.end())
    {
        showhelp();
        exit(0);
    }
    if(arguments.find("image") != arguments.end())
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

std::map<std::string, std::string> parsecommands(int argc, char *argv[])
{
    std::map<std::string, std::string> retvalue;
    std::list<std::string> arguments;
    std::list<std::string>::iterator iter;

    for (int i = 1; i != argc; i++)
    {
        arguments.push_back(argv[i]);
    }

    //iter = arguments.begin();
    for(iter = arguments.begin(); iter != arguments.end(); ++iter)
    {
        if((*iter) == "--image" || (*iter) == "-i")
        {
            ++iter;
            if(iter != arguments.end())
                retvalue["image"] = *iter;
            else
                --iter;
        }
        else if((*iter) == "--scale" || (*iter) == "-s")
        {
            retvalue["scale"] = "true";
        }
        else if((*iter) == "--version" || (*iter) == "-V")
        {
            retvalue["version"] = "true";
        }
        else if((*iter) == "--help" || (*iter) == "-h")
        {
            retvalue["help"] = "true";	
        }
        else if((*iter) == "--verbose" || (*iter) == "-v")
        {
            retvalue["verbose"] = "true";
        }
    }
/*
    }
    while (iter != arguments.end())
    {
        if((*iter) == "--image" && iter +1 != arguments.end())
        {
            retvalue["image"] = *++iter;
        }
        if((*iter) == "--scale")
        {
            retvalue["scale"] = "true";
        }
        if((*iter) == "--version")
        {
            retvalue["version"] = "true";
        }
        ++iter;
    }
*/
    return retvalue;
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
    << "-v    --verbose                 Verbose output\n";
}
