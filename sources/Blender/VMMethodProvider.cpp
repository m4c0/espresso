#include "VMMethodProvider.hpp"

using namespace Espresso::Blender;

VMMethodProvider::VMMethodProvider(Espresso::VM::ClassResolver * cr) : classResolver_(cr) {
}

void * VMMethodProvider::getNativeMethod(const char * className, const char * name, const char * signature) {
    auto cls = classResolver_->findClass(className);
    if (!cls) return 0;
    return cls->findMethod(name, signature);
}

