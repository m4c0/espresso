#ifndef ESPRESSO_BLENDER_JVMCLASS_H
#define ESPRESSO_BLENDER_JVMCLASS_H

#include "Class.hpp"
#include "Class/Base.hpp"

namespace Espresso {
    namespace Blender {
        class JVMClass : public Espresso::ClassParser::Class, public Espresso::VM::Class::Base {
        public:
            JVMClass(const char * filename);
            JVMClass(const char * data, int len);

            const char * name() const;

            void * findMethod(const char * name, const char * signature);
        private:
            class Method;
            Method * methods_;
        };
    };
};

#endif

