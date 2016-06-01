#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_NAMEANDTYPE_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_NAMEANDTYPE_H

#include "DataStream.hpp"
#include "Item.hpp"
#include "Manager.hpp"

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class NameAndType : public Item {
            public:
                NameAndType(Manager & mgr, DataStream & data);
            private:
                const Item * const * name;
                const Item * const * descriptor;
            };
        };
    };
};

#endif

