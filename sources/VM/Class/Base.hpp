#ifndef ESPRESSO_VM_CLASS_BASE_H
#define ESPRESSO_VM_CLASS_BASE_H

namespace Espresso {
    namespace VM {
        class ClassResolver;

        namespace Class {
            class Base {
            public:
                Base();
    
                ClassResolver * classResolver() const { return classResolver_; }
                void classResolver(ClassResolver *);

                virtual const char * name() const = 0;

                virtual void * findMethod(const char * name, const char * signature) = 0;
            private:
                ClassResolver * classResolver_;
            };
        };
    };
};

#endif

