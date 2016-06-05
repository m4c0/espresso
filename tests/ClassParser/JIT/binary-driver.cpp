#include "Class.hpp"
#include "JIT.hpp"
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
        std::cerr << "Driver must be called with the .bin file to test" << std::endl;
        return 1;
    }

    Espresso::Log = _log;

    std::ifstream in(argv[1], std::ios::in | std::ios::binary | std::ios::ate);
    if (!in) {
        std::cerr << "File not found: " << argv[1] << std::endl;
        return 2;
    }
    auto size = in.tellg();
    auto buffer = new char[size];
    in.seekg(0, std::ios::beg);
    in.read(buffer, size);

    Espresso::ClassParser::JIT jit(Espresso::ClassParser::DataStream(buffer, size));
    if (!jit) {
        std::cerr << jit.error() << std::endl;
        return 6;
    }

    void (*fn)() = (void (*)())jit.createFunction();
    if (!fn) return 7;

    delete buffer;
    return 0;
}

