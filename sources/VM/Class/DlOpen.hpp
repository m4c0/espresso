#ifndef ESPRESSO_VM_CLASS_DLOPEN_H
#define ESPRESSO_VM_CLASS_DLOPEN_H

#include "Class/Base.hpp"

namespace Espresso {
    namespace VM {
        namespace Class {
            class DlOpen : public Base {
            public:
                DlOpen(const char * name);

                const char * name() const { return name_; }

                void * findMethod(const char * name, const char * signature);
            private:
                const char * name_;
            };
        };
    };
};

#endif

