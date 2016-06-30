#ifndef ESPRESSO_VM_CLASS_PARSED_H
#define ESPRESSO_VM_CLASS_PARSED_H

#include "Class.hpp"
#include "Class/Base.hpp"

namespace Espresso {
    namespace VM {
        namespace Class {
            class Parsed : public Base {
            public:
                Parsed(Espresso::ClassParser::Class & cls);

                void * findMethod(const char * name, const char * signature) const;
            private:
                class Method;
                Method * methods_;
            };
        };
    };
};

#endif

