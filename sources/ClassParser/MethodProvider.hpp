#ifndef ESPRESSO_CLASSPARSER_METHODPROVIDER_H
#define ESPRESSO_CLASSPARSER_METHODPROVIDER_H

namespace Espresso {
    namespace ClassParser {
        class MethodProvider {
        public:
            virtual void * getNativeMethod(const char * className, const char * name, const char * signature) = 0;
        };
    };
};

#endif

