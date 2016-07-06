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

    int (*fn)(void *, int, int) = (int (*)(void *, int, int))vmp.getNativeMethod(cls->name(), "sum", "(II)I");
    if (!fn) {
        std::cerr << argv[1] << " does not contain sum(II)I" << std::endl;
        return 1;
    }

    if (fn(0, 0, 0) != 0) {
        std::cerr << "sum(0, 0) - expected 0, returned " << fn(0, 0, 0) << std::endl;
        return 1;
    }
    if (fn(0, 1, 6) != 7) {
        std::cerr << "sum(1, 6) - expected 7, returned " << fn(0, 1, 6) << std::endl;
        return 1;
    }
    if (fn(0, -1, 6) != 5) {
        std::cerr << "sum(-1, 6) - expected 5, returned " << fn(0, -1, 6) << std::endl;
        return 1;
    }

    return 0;
}

