#include "Parsed.hpp"

using namespace Espresso::VM::Class;

class Parsed::Method {
public:
    Method(const Espresso::ClassParser::Method & method, const Method * next) : next_(next) {
        code_ = method.code();
        name_ = method.name();
        signature_ = method.descriptor();
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

Parsed::Parsed(Espresso::ClassParser::Class & cls) : Base(cls.name()), methods_(0) {
    auto methods = cls.methods();
    while (*methods) {
        methods_ = new Method(*methods, methods_);
        methods++;
    }
}

void * Parsed::findMethod(const char * name, const char * signature) const {
    return methods_->findMethod(name, signature);
}

