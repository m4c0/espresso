#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_METHODREFINFO_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_METHODREFINFO_H

#include "DataStream.hpp"
#include "Item.hpp"
#include "Manager.hpp"

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class MethodRefInfo : public Item {
            public:
                MethodRefInfo(Manager & mgr, DataStream & data);
            private:
                const Item * const * className;
                const Item * const * nameAndType;
            };
        };
    };
};

#endif

