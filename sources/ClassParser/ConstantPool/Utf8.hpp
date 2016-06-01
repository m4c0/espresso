#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_UTF8_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_UTF8_H

#include "DataStream.hpp"
#include "Item.hpp"

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class Utf8 : public Item {
            public:
                Utf8(DataStream & data);
                ~Utf8();
            private:
                const char * value;
            };
        };
    };
};

#endif

