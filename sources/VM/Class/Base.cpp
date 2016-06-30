#include "Base.hpp"

using namespace Espresso::VM::Class;

Base::Base(const char * name) : name_(name) {
}

void Base::classResolver(ClassResolver * cr) {
    if (classResolver_ != 0) {
        // TODO: Eventually, make a warning or even allow it
        return;
    }
    classResolver_ = cr;
}

