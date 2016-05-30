#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_ITEM_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_ITEM_H

#include "Failable.hpp"

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class Item : public Failable {
            public:
                Item() : Failable(), tag(0) {}
                Item(int tag) : Failable(), tag(tag) {}
            private:
                const int tag;
            };
        };
    };
};

#endif

