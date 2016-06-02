cmake_minimum_required(VERSION 3.5) # I tested on 3.5 - feel free to test on lower ones and do a pull-request :)
project(espresso VERSION 0.0.1 LANGUAGES CXX)

option(BUILD_TESTS "Turn on if you want to build (and probably run) the tests" ON)
option(USE_CPP_STL "Adds some convenience binds to C++ standard library")

if(USE_CPP_STL)
    add_definitions(-DUSE_CPP_STL) # Eventually, this may go on a "config.h"
endif()

add_subdirectory(sources)

if(BUILD_TESTS)
    enable_testing()

    if(USE_CPP_STL)
        add_subdirectory(tests) # Tests heavily requires STL
    endif()
endif()

