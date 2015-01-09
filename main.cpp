#include "cmdparser.h"
#include <iostream>

/**
//  This is an example program of the command line parsing
//  class.
**/
int main(int argc, char* argv[])
{
    // declare and initialize the variables to pass the command line
    // values into
    std::vector<std::string> values, extraArgs;
    std::string str1;
    int int1 = 0;
    double double1 = 0.0;
    bool bool1 = false;

    // Create a parsing object and set an option of each type
    CmdTools::CmdParser argParser("CmdParserTest [options] [values]\n"
                        " return codes:\n"
                        " \t0 Success\n"
                        " \t1 Failure",
                        "-str",    "%s", &str1,    "pass a string",
                        "-int",    "%d", &int1,    "pass an int",
                        "-double", "%f", &double1, "pass a double",
                        "-bool",   "%b", &bool1,   "bool flag",
                        nullptr);
    
    // parse the command line, and check the result for success
    if (argParser.parse(argc, argv, extraArgs))
    {
        std::cout << "Unknown option used\n";
        argParser.usage();
        return 1;
    }
        
    // if -h was passed in print the usage 
    if (argParser.help())
    {
        argParser.usage();
        return 0;
    }

    // output the variables set by the command line options
    //  Note that if no option was passed the output is the
    //  initialization value.
    std::cout << "-str option passed in " << str1;
    std::cout << "\n-int option passed in " << int1;
    std::cout << "\n-double option passed in "<< double1;
    if (bool1)
        std::cout << "\n-bool flag was set\n";
    else
        std::cout << "\n";
    
    for (size_t i = 0; i < extraArgs.size(); ++i)
        std::cout << "Extra argument "<< i <<" : "<<extraArgs[i] << "\n";

    std::cout << std::endl;

    return 0;
}   
