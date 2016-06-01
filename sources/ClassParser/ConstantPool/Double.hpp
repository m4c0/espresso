#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_DOUBLE_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_DOUBLE_H

#include "DataStream.hpp"
#include "Item.hpp"

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class Double : public Item {
            public:
                Double(DataStream & data);
            private:
                double value;
            };
        };
    };
};

#endif

