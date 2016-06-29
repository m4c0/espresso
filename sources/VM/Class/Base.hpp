#ifndef ESPRESSO_VM_CLASS_BASE_H
#define ESPRESSO_VM_CLASS_BASE_H

namespace Espresso {
    namespace VM {
        namespace Class {
            class Base {
            public:
                Base(const char * name);
    
                const char * name() const { return name_; }
    
                void addMethod(const char * name, const char * signature, void * fn);
                void * findMethod(const char * name, const char * signature);
            private:
                const char * name_;
            };
        };
    };
};

#endif

