#include "Class/DlOpen.hpp"
#include "JVMClass.hpp"
#include "ClassResolver.hpp"
#include "Logger.hpp"
#include "VMMethodProvider.hpp"

#include <iostream>

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

    auto cls = new Espresso::Blender::JVMClass(argv[1]);
    if (!*cls) {
        std::cerr << argv[1] << " wasn't loaded: " << cls->error() << std::endl;
        return 1;
    }
    classdb.addClass(cls);

    auto vmp = Espresso::Blender::VMMethodProvider(&classdb);

    int (*fn)(int) = (int (*)(int))vmp.getNativeMethod(cls->name(), "fib", "(I)I");
    if (!fn) {
        std::cerr << argv[1] << " does not contain fib(I)I" << std::endl;
        return 1;
    }

    if (fn(1) != 1) {
        std::cerr << "fib(1) - expected 1, returned " << fn(1) << std::endl;
        return 1;
    }
    if (fn(5) != 8) {
        std::cerr << "fib(5) - expected 8, returned " << fn(5) << std::endl;
        return 1;
    }

    return 0;
}

