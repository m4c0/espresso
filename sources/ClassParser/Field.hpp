#ifndef ESPRESSO_CLASSPARSER_FIELD_H
#define ESPRESSO_CLASSPARSER_FIELD_H

#include "ClassEntry.hpp"
#include "ConstantPool/Manager.hpp"

namespace Espresso {
    namespace ClassParser {
        class Field : public ClassEntry {
        public:
            Field(ConstantPool::Manager & cpool, DataStream & data);
        };
    };
};

#endif

