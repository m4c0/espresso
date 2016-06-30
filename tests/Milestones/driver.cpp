#include "Class/DlOpen.hpp"
#include "Class/Parsed.hpp"
#include "ClassResolver.hpp"
#include "Logger.hpp"

#include <iostream>

static int _result = 0;

extern "C" void ZN4java4lang6System4exitEi(int code) {
    std::cerr << "java/lang/System.exit(I)V called with code: " << code << std::endl;
    _result = code;
}

static void _log(const char * fmt, ...) {
    va_list va;
    va_start(va, fmt);
    vfprintf(stderr, fmt, va);
    va_end(va);

    std::cerr << std::endl;
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        std::cerr << "Test must be called with the path to the test class" << std::endl;
        return 1;
    }

    Espresso::Log = _log;

    auto classdb = Espresso::VM::ClassResolver();
    classdb.addClass(new Espresso::VM::Class::DlOpen("java/lang/Object"));
    classdb.addClass(new Espresso::VM::Class::DlOpen("java/lang/System"));

    auto cls = Espresso::ClassParser::Class(argv[1]);
    if (!cls) {
        std::cerr << argv[1] << " wasn't loaded: " << cls.error() << std::endl;
        return 1;
    }
    auto pcls = new Espresso::VM::Class::Parsed(cls);
    classdb.addClass(pcls);

    void (*fn)() = (void (*)())pcls->findMethod("<clinit>", "()V");
    if (!fn) {
        std::cerr << argv[1] << " does not contain <clinit>()V" << std::endl;
        return 1;
    }

    fn();

    if (_result != 99) {
        std::cerr << "java/lang/System.exit(I)V was not properly called" << std::endl;
        return 99;
    }
    return 0;
}

