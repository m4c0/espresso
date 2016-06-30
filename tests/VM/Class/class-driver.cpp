#include "Class.hpp"
#include "Class/Parsed.hpp"
#include "Logger.hpp"

#include <iostream>

void _log(const char * fmt, ...) {
    va_list va;
    va_start(va, fmt);
    vfprintf(stderr, fmt, va);
    va_end(va);

    std::cerr << std::endl;
}

int main(int argc, char ** argv) {
    if (argc < 4) {
        std::cerr << "Driver must be called with the .class file to test and methods to find" << std::endl;
        return 1;
    }
    // Remove exe, class and the rest is (method, signature)
    auto count = (argc - 2);
    if (count % 2 == 1) {
        std::cerr << "Driver must be called with the class file, plus pairs of method name and signature" << std::endl;
        return 2;
    }

    Espresso::Log = _log;

    auto cp = Espresso::ClassParser::Class(argv[1]);
    auto cls = Espresso::VM::Class::Parsed(cp);

    for (int i = 2; i < argc; i += 2) {
        if (!cls.findMethod(argv[i], argv[i + 1])) {
            std::cerr << "Could not find " << argv[i] << argv[i + 1] << std::endl;
            return 3;
        }
    }

    return 0;
}

