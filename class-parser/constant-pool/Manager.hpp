#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_H

#include "DataStream.hpp"
#include "Item.hpp"

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class Manager : public Failable {
            public:
                Manager(DataStream & data);
                ~Manager();

                const Item * const * operator[](int idx) const;
            private:
                Item ** items;
                int size;
            };
        };
    };
};

#endif

