#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_REFINFO_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_REFINFO_H

#include "DataStream.hpp"
#include "Item.hpp"
#include "Manager.hpp"

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class RefInfo : public Item {
            public:
                RefInfo(Manager & mgr, DataStream & data, int tag);

                const char * className() const;
                const char * name() const;
                const char * descriptor() const;
            private:
                const Item * const * classInfo;
                const Item * const * nameAndType;
            };
        };
    };
};

#endif

