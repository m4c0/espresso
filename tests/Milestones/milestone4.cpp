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

extern "C" void ZN4java4lang6ObjectC1Ev() {}

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

    auto fn = (bool (*)(int))vmp.getNativeMethod(cls->name(), "contains", "(I)Z");
    if (!fn) {
        std::cerr << argv[1] << " does not contain contains(I)Z" << std::endl;
        return 1;
    }

    if (fn(10)) return 2;
    if (!fn(98)) return 3;
    if (!fn(12)) return 4;
    if (!fn(3)) return 5;

    return 0;
}

