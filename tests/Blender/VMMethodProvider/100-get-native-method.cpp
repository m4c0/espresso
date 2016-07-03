#include "Class/DlOpen.hpp"
#include "VMMethodProvider.hpp"

extern "C" void ZN9SomeClass6methodEv() {}
extern "C" void ZN10OtherClass6methodEv() {}

int main() {
    auto cr = Espresso::VM::ClassResolver();
    auto vmp = Espresso::Blender::VMMethodProvider(&cr);

    // Let's not crash with no classes on CR
    if (vmp.getNativeMethod("Nope", "no", "()V") != 0) return 1;

    auto class1 = Espresso::VM::Class::DlOpen("SomeClass");
    cr.addClass(&class1);

    // Let's not crash with undefined class
    if (vmp.getNativeMethod("Nope", "no", "()V") != 0) return 2;
    // Let's not crash with undefined method
    if (vmp.getNativeMethod("SomeClass", "no", "()V") != 0) return 3;
    // Valid method
    if (vmp.getNativeMethod("SomeClass", "method", "()V") != ZN9SomeClass6methodEv) return 4;

    auto class2 = Espresso::VM::Class::DlOpen("OtherClass");
    cr.addClass(&class2);

    // Same tests works with more classes
    if (vmp.getNativeMethod("Nope", "no", "()V") != 0) return 5;
    if (vmp.getNativeMethod("SomeClass", "no", "()V") != 0) return 6;
    if (vmp.getNativeMethod("SomeClass", "method", "()V") != ZN9SomeClass6methodEv) return 7;
    // And we can retrieve the new class' method
    if (vmp.getNativeMethod("OtherClass", "method", "()V") != ZN10OtherClass6methodEv) return 8;

    return 0;
}

