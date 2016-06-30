#include "Class/DlOpen.hpp"
#include "Class/Parsed.hpp"
#include "ClassResolver.hpp"

#include <iostream>

static int _result = 0;

extern "C" void ZN4java4lang6System4exitEi(int code) {
    std::cerr << "java/lang/System.exit(I)V called with code: " << code << std::endl;
    _result = code;
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        std::cerr << "Test must be called with the path to the test class" << std::endl;
        return 1;
    }

    auto classdb = Espresso::VM::ClassResolver();
    classdb.addClass(new Espresso::VM::Class::DlOpen("java/lang/Object"));
    classdb.addClass(new Espresso::VM::Class::DlOpen("java/lang/System"));

    auto cls = Espresso::ClassParser::Class(argv[1]);
    classdb.addClass(new Espresso::VM::Class::Parsed(cls));

    // Remaining Tasks:
    // 1. Pass CR to VM
    // 2. Ask VM to init "argv[1]"
    // 3. ...
    // 4. Profit!

    if (_result != 99) {
        std::cerr << "java/lang/System.exit(I)V was not properly called" << std::endl;
        return 99;
    }
    return 0;
}

