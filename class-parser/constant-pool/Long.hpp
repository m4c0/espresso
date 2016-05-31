#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_LONG_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_LONG_H

#include "DataStream.hpp"
#include "Item.hpp"

#include <cstdint>

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class Long : public Item {
            public:
                Long(DataStream & data);
            private:
                int64_t value;
            };
        };
    };
};

#endif

