#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_FLOAT_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_FLOAT_H

#include "DataStream.hpp"
#include "Item.hpp"

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class Float : public Item {
            public:
                Float(DataStream & data);
            private:
                float value;
            };
        };
    };
};

#endif

