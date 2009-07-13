#include <string>

#include "main.h"
#include "pwandebug.h"
#include "pwanstrings.h"
#include "pwancmdlineparser.h"
#include "imageviewer_frontend_qt.h"
#include "../config.h"

int main (int argc, char *argv[])
{
    pwan::debug debug;
    pwan::t_cmdlineParser cmdlineParser;
    pwan::imageviewer_frontend_qt imageviewer(argc, argv); // = new pwan::imageviewer_frontend_qt(argc, argv);
    std::string imageFileName;
    std::string functionName("main");
    std::vector<pwan::optionsReturn> parsedOpts;

    imageviewer.init();
    //set the commandline/inifile allowed options
    cmdlineParser.setAllowedOption("v", "verbose", "Verbose output", pwan::NO_PARAMETER);
    cmdlineParser.setAllowedOption("h", "help", "This helptext", pwan::NO_PARAMETER);
    cmdlineParser.setAllowedOption("V", "version", "Prints versionstring", pwan::NO_PARAMETER);
    cmdlineParser.setAllowedOption("d", "debug", "Be extra verbose on output", pwan::NO_PARAMETER);
    cmdlineParser.setAllowedOption("s", "scale", "Auto scale the image to fit the screen", pwan::NO_PARAMETER);
    cmdlineParser.setAllowedOption("i", "image", "Specifies the image you want to load", pwan::DEFAULT_PARAMETER);

    //Check the commandline
    cmdlineParser.checkCmdLine(argc, argv);
    parsedOpts = cmdlineParser.returnFoundOptions();
    for(std::vector<pwan::optionsReturn>::iterator it = parsedOpts.begin(); it != parsedOpts.end(); ++it)
    {
        if(it->option == "verbose")
        {   if(debug.getDebugLevel() <= 2)
            {   debug.setDebugLevel(2);}}
        else if(it->option == "debug")
            debug.setDebugLevel(3);
        else if(it->option == "version")
        {
            debug.dprint(std::string(PACKAGE_NAME) + " v" + PACKAGE_VERSION + "\n");;
            return 0;
        }
        else if(it->option == "help")
        {
            debug.dprint(cmdlineParser.makeHelp());
            return 0;
        }
        else if(it->option == "image")
        {
            imageFileName = it->parameter;
        }
        else if(it->option == "scale")
        {
            imageviewer.setScaled(true);
        }
    }
    debug.dprint(functionName, std::string(PACKAGE_NAME) + " v" + PACKAGE_VERSION, 3);
    debug.dprint(functionName, "", 3);
    debug.dprint(functionName, "Raw Commandline:", 3);
    debug.dprint(functionName, "=================================", 3);
    for(int teller = 0; teller != argc; ++teller)
        debug.dprint(functionName, std::string("argc = ") + pwan::strings::fromInt(teller) + "; " + argv[teller], 3);
    debug.dprint(functionName, "", 3);
    debug.dprint(functionName, "All Options Parsed:", 3);
    debug.dprint(functionName, "=================================", 3);
    for(std::vector<pwan::optionsReturn>::iterator it = parsedOpts.begin(); it != parsedOpts.end(); ++it)
    {
        debug.dprint(functionName, it->option + " : " + it->parameter, 3);
    }
    debug.dprint(functionName, "", 3);

    if(imageFileName != "")
    {
        if(!imageviewer.startimageviewer(imageFileName))
        {
            debug.dprint("Could not load specified file...");
            exit(1);
        }
        return imageviewer.startup();
    }
    else
    {
        debug.dprint(std::string(PACKAGE_NAME) + " v" + PACKAGE_VERSION);
        debug.dprint("Missing option");
        debug.dprint(std::string("Usage: ") + PACKAGE_NAME + " [OPTION]");
        debug.dprint(std::string("Try: `" ) + PACKAGE_NAME + " --help` for more options.");
        exit(0);
    }
}
