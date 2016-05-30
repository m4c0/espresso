#include "Class.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char ** argv) {
    if (argc != 2) return 1;

    std::string file(argv[1]);
    auto shouldPass = file.find(".fail.") == std::string::npos;

    std::ifstream in(file, std::ios::in | std::ios::binary | std::ios::ate);
    auto size = in.tellg();

    auto buffer = new char[size];
    in.seekg(0, std::ios::beg);
    in.read(buffer, size);

    Espresso::ClassParser::Class cls(buffer, size);
    if (!cls) {
        std::cerr << cls.error() << std::endl;
    }
    if (cls == shouldPass) return 0;
    
    return 2;
}

