#ifndef ESPRESSO_CLASSPARSER_ATTRIBUTE_CODE_H
#define ESPRESSO_CLASSPARSER_ATTRIBUTE_CODE_H

#include "Attributed.hpp"
#include "ConstantPool/Manager.hpp"
#include "DataStream.hpp"
#include "JIT.hpp"
#include "MethodProvider.hpp"

namespace Espresso {
    namespace ClassParser {
        namespace Attribute {
            class Code : public Base, public Attributed { // Yes, code is an attribute with attributes
            public:
                Code();
                Code(ConstantPool::Manager & cpool, DataStream & data);

                JIT code() const { return code_; }
            private:
                JIT code_;
            };
        };
    };
};

#endif

