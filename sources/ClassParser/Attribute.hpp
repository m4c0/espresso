#ifndef ESPRESSO_CLASSPARSER_ATTRIBUTE_H
#define ESPRESSO_CLASSPARSER_ATTRIBUTE_H

#include "ConstantPool/Manager.hpp"
#include "DataStream.hpp"
#include "Failable.hpp"

namespace Espresso {
    namespace ClassParser {
        class Attribute : public Failable {
        public:
            Attribute(ConstantPool::Manager & cpool, DataStream & data);
        };
    };
};

#endif

