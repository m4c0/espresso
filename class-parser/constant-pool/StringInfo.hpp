#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_STRINGINFO_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_STRINGINFO_H

#include "DataStream.hpp"
#include "Item.hpp"
#include "Manager.hpp"

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class StringInfo : public Item {
            public:
                StringInfo(Manager & mgr, DataStream & data);
            private:
                const Item * const * utf8;
            };
        };
    };
};

#endif

