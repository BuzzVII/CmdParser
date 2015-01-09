#include <iostream>
#include <string.h>
#include <cstdlib>

#include "cmdparser.h"

namespace CmdTools{
CmdParser::CmdParser(const char* usage...):
    m_usage(usage), m_help(false)
{
    va_list args;
    va_start(args, usage);
    char * p_char = va_arg(args, char*);
    while(p_char != nullptr){
        m_type[p_char]   = va_arg(args, char*);
        m_values[p_char] = va_arg(args, char*);
        m_helpString.push_back(va_arg(args, char*));
        p_char = va_arg(args, char*);
    }
    va_end(args);
}


int CmdParser::parse(int argc, char* argv[], 
        std::vector<std::string> &extraOpts)
{
    for (int i = 1; i < argc; ++i){
        if (!strcmp(argv[i], "-h")){
            m_help = true;
            return 0;
        }

        if (argv[i][0] == '-'){
            if (m_values.count(argv[i]) > 0){
                if (!strcmp(m_type[argv[i]], "%s") && i+1 < argc){
                    std::string* ptr = reinterpret_cast<std::string*> (m_values[argv[i]]);
                    *ptr = argv[++i];
                }
                else if (!strcmp(m_type[argv[i]], "%d") && i+1 < argc){
                    int* ptr = reinterpret_cast<int*> (m_values[argv[i]]);
                    *ptr = atoi(argv[++i]);
                }
                else if (!strcmp(m_type[argv[i]], "%f") && i+1 < argc){
                    double* ptr = reinterpret_cast<double*> (m_values[argv[i]]);
                    *ptr = atof(argv[++i]);
                }
                else if (!strcmp(m_type[argv[i]], "%b")){
                    bool* ptr = reinterpret_cast<bool*> (m_values[argv[i]]);
                    *ptr = true;
                }
                else return 1;
           }
           else{
               return 1;
           }
        }
        else{
            extraOpts.push_back(argv[i]);
        }
    }

    return 0;
}

void CmdParser::usage() const
{
    std::cout << m_usage << std::endl;
    int i = 0;

    for (auto it = m_values.begin(); it != m_values.end(); it++){
        std::cout << it->first << "\t\t" << m_helpString[i] << "\n";
        i++;
    } 
    std::cout << "-h\t\tReturns this message\n"; 
}

bool CmdParser::help() const
{
    return m_help;        
}

}//namespace 
