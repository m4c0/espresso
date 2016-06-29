#ifndef ESPRESSO_VM_CLASSRESOLVER_H
#define ESPRESSO_VM_CLASSRESOLVER_H

#include "Class/Base.hpp"

namespace Espresso {
    namespace VM {
        class ClassResolver {
        public:
            void addClass(Class::Base & cls);
            Class::Base & findClass(const char * name);
        };
    };
};

#endif

