#include "Class.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char ** argv) {
    if (argc != 2) {
        std::cerr << "Driver must be called with the .class file to test" << std::endl;
        return 1;
    }

    std::ifstream in(argv[1], std::ios::in | std::ios::binary | std::ios::ate);
    if (!in) {
        std::cerr << "File not found: " << argv[1] << std::endl;
        return 2;
    }

    auto size = in.tellg();

    auto buffer = new char[size];
    in.seekg(0, std::ios::beg);
    in.read(buffer, size);

    Espresso::ClassParser::Class cls(buffer, size);
    if (!cls) {
        std::cerr << cls.error() << std::endl;
        return 3;
    }
    return 0;
}

