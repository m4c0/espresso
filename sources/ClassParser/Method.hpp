#ifndef ESPRESSO_CLASSPARSER_METHOD_H
#define ESPRESSO_CLASSPARSER_METHOD_H

#include "Attribute/Code.hpp"
#include "ClassEntry.hpp"
#include "ConstantPool/Manager.hpp"
#include "MethodProvider.hpp"

namespace Espresso {
    namespace ClassParser {
        class Method : public ClassEntry {
        public:
            Method();
            Method(ConstantPool::Manager & cpool, DataStream & data);

            void * buildFunction(MethodProvider * methods) const { return code_.buildFunction(methods); }

        private:
            Attribute::Code code_;
        };
    };
};

#endif

