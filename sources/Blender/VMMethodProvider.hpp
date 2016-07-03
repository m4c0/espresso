#ifndef ESPRESSO_BLENDER_VMMETHODPROVIDER_H
#define ESPRESSO_BLENDER_VMMETHODPROVIDER_H

#include "ClassResolver.hpp"
#include "MethodProvider.hpp"

namespace Espresso {
    namespace Blender {
        class VMMethodProvider : public Espresso::ClassParser::MethodProvider {
        public:
            VMMethodProvider(Espresso::VM::ClassResolver * cr);

            void * getNativeMethod(const char * className, const char * name, const char * signature);
        private:
            Espresso::VM::ClassResolver * classResolver_;
        };
    };
};

#endif

