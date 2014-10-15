#ifndef CMDPARSER_H
#define CMDPARSER_H

#include <string>
#include <map>
#include <cstdarg>
#include <vector>

namespace CmdTools{

/**
/
/  This class is used to create an object for parsing
/   command line arguments.
/
/   It needs to be initialized with the options that are
/   used for the program. The variables to assign the parsed
/   inputs need to be initialized because their value is not
/   assigned if no option is parsed. Example initialization:
/
/    CmdTools::CmdParser argParser("CmdParserTest [options] [values]\n"
/                        " return codes:\n"
/                        " 0 Success\n"
/                        " 1 Failure",
/                        "-str",    "%s", &str1,    "pass a string",
/                        "-int",    "%d", &int1,    "pass an int",
/                        "-double", "%f", &double1, "pass a double",
/                        "-bool",   "%b", &bool1,   "bool flag",
/                        nullptr);
/
/   The options list is terminated with a nullptr. If no options are
/   used a usage string and nullptr need to be passed in.
/
/   When parsed arguments that don't have an associated option tag
/   are pushed into the extraOpts argument in the parse method.
/
**/

class CmdParser
{
    public:
        /*
        /  Constructor for the parser. It requires a usage
        /   string and can then be followed by optional
        /   arguments in sets of four; command line
        /   option, type of variable, variable to assign,
        /   and help information.
        /  The initialization options are added to the parser
        /   for use when parsing the command line arguments.
        /  A nullptr must be passed as the final argument.
        */
        CmdParser(const char* usage...);

        /*
        /  Takes the argc and argv[] passed in to the main
        /   function along with a variable that stores all
        /   arguments with out an option.
        /  The arguments are then parsed based on the 
        /   initialization parameters.
        /   returns 0 on success.
        */
        int parse(int argc, char* argv[], 
                std::vector<std::string> &extraOpts);

        /*
        /  prints the usage information of the program based on
        /   the initialization parameters. 
        */
        void usage() const;
        
        /*
        /  returns the state of the m_help member variable
        /   m_help is set to true if -h is passed as an option 
        */
        bool help() const;

    private:
        CmdParser(){}

        std::map<std::string, char*> m_values;
        std::map<std::string, char*> m_type;
        std::vector<std::string>     m_helpString;
        std::string m_usage;
        bool m_help = false;
};

}

#endif
