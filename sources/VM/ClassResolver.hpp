#ifndef ESPRESSO_VM_CLASSRESOLVER_H
#define ESPRESSO_VM_CLASSRESOLVER_H

#include "Class/Base.hpp"

namespace Espresso {
    namespace VM {
        class ClassResolver {
        public:
            ClassResolver();

            void addClass(Class::Base * cls);
            Class::Base * findClass(const char * name);

        private:
            class Node;
            Node * first_;
        };
    };
};

#endif

