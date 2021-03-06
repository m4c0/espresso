#include "Class.hpp"
#include "Logger.hpp"

#include <cstdio>
#include <iostream>
#include <fstream>

void _log(const char * fmt, ...) {
    va_list va;
    va_start(va, fmt);
    vfprintf(stderr, fmt, va);
    va_end(va);

    std::cerr << std::endl;
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        std::cerr << "Driver must be called with the .class file to test" << std::endl;
        return 1;
    }

    Espresso::Log = _log;

    Espresso::ClassParser::Class cls(argv[1]);
    if (!cls) {
        std::cerr << cls.error() << std::endl;
        return 3;
    }
    return 0;
}

