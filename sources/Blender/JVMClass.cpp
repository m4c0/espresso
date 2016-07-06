#include "JVMClass.hpp"

#include "VMMethodProvider.hpp"

#include <string.h>

using namespace Espresso::Blender;

class JVMClass::Method {
public:
    Method(const Espresso::ClassParser::Method * method) : code_(0) {
        jit_ = method->code();
        name_ = method->name();
        signature_ = method->descriptor();

        method++;
        next_ = *method ? new Method(method) : 0;
    }

    Method * findMethod(const char * name, const char * signature) {
        if ((strcmp(name, name_) == 0) && (strcmp(signature, signature_) == 0)) {
            return this;
        }
        if (!next_) return 0;
        return next_->findMethod(name, signature);
    }

    Espresso::ClassParser::JIT jit_;
    const char * name_;
    const char * signature_;

    void * code_;

    Method * next_;
};

JVMClass::JVMClass(const char * filename) : Class(filename), Base(), methods_(0) {
}
JVMClass::JVMClass(const char * data, int len) : Class(data, len), Base(), methods_(0) {
}

const char * JVMClass::name() const {
    return Class::name();
}

void * JVMClass::findMethod(const char * method, const char * signature) {
    if (!methods_) {
        methods_ = methods() ? new Method(methods()) : 0;
    }
    auto owner = methods_->findMethod(method, signature);
    if (!owner) return 0;

    if (!owner->code_) {
        auto vmp = VMMethodProvider(classResolver());
        owner->code_ = owner->jit_.className(name()).buildFunction(&vmp);
    }

    return owner->code_;
}

