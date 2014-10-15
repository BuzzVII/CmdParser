#include "cmdparser.h"
#include <iostream>

/**
//  This is an example program of the command line parsing
//  class.
**/
int main(int argc, char* argv[])
{
    std::vector<std::string> values, extraArgs;
    std::string str1;
    int int1 = 0;
    double double1 = 0.0;
    bool bool1 = false;

    CmdTools::CmdParser argParser("CmdParserTest [options] [values]",
                        "-str",    "%s", &str1,    "pass a string",
                        "-int",    "%d", &int1,    "pass an int",
                        "-double", "%f", &double1, "pass a double",
                        "-bool",   "%b", &bool1,   "bool flag",
                        nullptr);
        
    if (argParser.parse(argc, argv, extraArgs))
    {
        std::cout << "Unknown option used\n";
        argParser.usage();
        return 1;
    }
        

    if (argParser.help())
    {
        argParser.usage();
        return 0;
    }

    std::cout << str1 << " " << int1 << " "<< double1;
    if (bool1)
        std::cout << " true\n";
    else
        std::cout << "\n";

    for (size_t i = 0; i < extraArgs.size(); ++i)
        std::cout << extraArgs[i] << " ";

    std::cout << std::endl;
    return 0;
}   
