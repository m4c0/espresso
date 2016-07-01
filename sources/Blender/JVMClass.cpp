#include "JVMClass.hpp"

#include <string.h>

using namespace Espresso::Blender;

class JVMClass::Method {
public:
    Method(const Espresso::ClassParser::Method * method) {
        code_ = method->code();
        name_ = method->name();
        signature_ = method->descriptor();

        method++;
        next_ = *method ? new Method(method) : 0;
    }

    void * findMethod(const char * name, const char * signature) const {
        if ((strcmp(name, name_) == 0) && (strcmp(signature, signature_) == 0)) {
            return code_;
        }
        if (!next_) return 0;
        return next_->findMethod(name, signature);
    }

    const char * name_;
    const char * signature_;
    void * code_;

    const Method * next_;
};

JVMClass::JVMClass(const char * filename) : Class(filename), Base(), methods_(0) {
    methods_ = methods() ? new Method(methods()) : 0;
}
JVMClass::JVMClass(const char * data, int len) : Class(data, len), Base(), methods_(0) {
    methods_ = methods() ? new Method(methods()) : 0;
}

const char * JVMClass::name() const {
    return Class::name();
}

void * JVMClass::findMethod(const char * name, const char * signature) {
    return methods_->findMethod(name, signature);
}

