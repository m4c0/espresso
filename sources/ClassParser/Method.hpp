#ifndef ESPRESSO_CLASSPARSER_METHOD_H
#define ESPRESSO_CLASSPARSER_METHOD_H

#include "ClassEntry.hpp"
#include "ConstantPool/Manager.hpp"

namespace Espresso {
    namespace ClassParser {
        class Method : public ClassEntry {
        public:
            Method(ConstantPool::Manager & cpool, DataStream & data);
        };
    };
};

#endif

