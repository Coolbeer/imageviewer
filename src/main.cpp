#include <string>
#include <QApplication>

#include "../config.h"

#include "main.h"
#include "t_imageviewer.h"
#include "pwandebug.h"
#include "pwanoptions.h"
#include "pwanstrings.h"
#include "pwancmdlineparser.h"

pwan::options options;
pwan::debug debug;

int main (int argc, char *argv[])
{
    std::string functionName("main");
    std::string imageFileName;
    std::vector<pwan::optionsReturn> parsedOpts;
    QApplication app(argc, argv);
    pwan::t_cmdlineParser cmdlineParser;

    //set the commandline/inifile allowed options
    cmdlineParser.setAllowedOption("v", "verbose", "Verbose output", pwan::NO_PARAMETER);
    cmdlineParser.setAllowedOption("h", "help", "This helptext", pwan::NO_PARAMETER);
    cmdlineParser.setAllowedOption("V", "version", "Prints versionstring", pwan::NO_PARAMETER);
    cmdlineParser.setAllowedOption("d", "debug", "Be extra verbose on output", pwan::NO_PARAMETER);
    cmdlineParser.setAllowedOption("s", "scale", "Auto scale the image to fit the screen", pwan::NO_PARAMETER);
    cmdlineParser.setAllowedOption("i", "image", "Specifies the image you want to load", pwan::DEFAULT_PARAMETER);

    //Check the commandline
    if(cmdlineParser.checkCmdLine(argc, argv) != pwan::P_OK)
    {
        debug.print("humm\n");
    }
    parsedOpts = cmdlineParser.returnFoundOptions();
    for(unsigned int i=0; i != parsedOpts.size(); ++i)
    {
        if(parsedOpts.at(i).parameter == "")
            options.set(parsedOpts.at(i).option, "true");
        else
            options.set(parsedOpts.at(i).option, parsedOpts.at(i).parameter);
    }
    if(options.get("verbose") == "true")
        debug.setDebugLevel(2);
    if(options.get("debug") == "true")
        debug.setDebugLevel(3);

    debug.print(functionName, std::string(PACKAGE_NAME) + " v" + PACKAGE_VERSION, 3);
    debug.print(functionName, "", 3);
    debug.print(functionName, "Raw Commandline:", 3);
    debug.print(functionName, "=================================", 3);
    for(int teller = 0; teller != argc; ++teller)
        debug.print(functionName, std::string("argc = ") + pwan::strings::fromInt(teller) + "; " + argv[teller], 3);
    debug.print(functionName, "", 3);
    std::list<std::string> hepp = options.dump();
    debug.print(functionName, "All Options Parsed:", 3);
    debug.print(functionName, "=================================", 3);
    std::list<std::string>::iterator mapiter = hepp.begin();
    while(mapiter != hepp.end())
    {
        std::string output;
        output = (*mapiter);
        ++mapiter;
        output += " : " + (*mapiter);;
        debug.print(functionName, output, 3);
        ++mapiter;
    }
    debug.print(functionName, "", 3);

    if(options.get("version") == "true")
    {
        debug.print(std::string(PACKAGE_NAME) + " v" + PACKAGE_VERSION + "\n");;
        exit(0);
    }
    else if(options.get("help") == "true")
    {
        debug.print(cmdlineParser.makeHelp());
        exit(0);
    }

    t_imageviewer *imageviewer = new t_imageviewer;
    imageFileName = options.get("image");
    if(imageFileName != "")
    {
        if(!imageviewer->startimageviewer(imageFileName))
        {
            debug.print("Could not load specified file...");
            exit(1);
        }
        imageviewer->show();
        return app.exec();
    }
    else
    {
        debug.print(std::string(PACKAGE_NAME) + " v" + PACKAGE_VERSION);
        debug.print("Missing option");
        debug.print(std::string("Usage: ") + PACKAGE_NAME + " [OPTION]");
        debug.print(std::string("Try: `" ) + PACKAGE_NAME + " --help` for more options.");
        exit(0);
    }
}
