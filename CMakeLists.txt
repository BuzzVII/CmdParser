cmake_minimum_required(VERSION 2.8) 

set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -fopenmp"
    CACHE STRING "Flags used by the compiler during all build types.")

project(cmd_parser)

add_library(CmdParser cmdparser.cpp)

add_executable(CmdDemo main.cpp)

target_link_libraries(CmdDemo CmdParser)
