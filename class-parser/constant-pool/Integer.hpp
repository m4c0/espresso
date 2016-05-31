#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_INTEGER_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_INTEGER_H

#include "DataStream.hpp"
#include "Item.hpp"

#include <cstdint>

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class Integer: public Item {
            public:
                Integer(DataStream & data);
            private:
                int32_t value;
            };
        };
    };
};

#endif

