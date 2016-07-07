#include "Class/DlOpen.hpp"
#include "JVMClass.hpp"
#include "Logger.hpp"
#include "VMMethodProvider.hpp"

#include <iostream>

static int _called_code = 0;
extern "C" void ZN4java4lang6System4exitEi(int code) {
    _called_code = code;
}

int main(int argc, char ** argv) {
    if (argc < 2) {
        std::cerr << "Driver must be called with the .class file to test" << std::endl;
        return 1;
    }

    auto cls = new Espresso::Blender::JVMClass(argv[1]);

    auto classdb = new Espresso::VM::ClassResolver();
    classdb->addClass(new Espresso::VM::Class::DlOpen("java/lang/System"));
    classdb->addClass(cls);

    auto vmp = Espresso::Blender::VMMethodProvider(classdb);
    vmp.getNativeMethod(cls->name(), "test", "()V"); // use another method just to check if <clinit> is called

    return _called_code == 99 ? 0 : 2;
}

