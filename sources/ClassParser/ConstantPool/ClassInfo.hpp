#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_CLASSINFO_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_CLASSINFO_H

#include "DataStream.hpp"
#include "Item.hpp"
#include "Manager.hpp"

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class ClassInfo : public Item {
            public:
                ClassInfo(Manager & mgr, DataStream & data);

                const char * className(Manager & mgr) const;
            private:
                int className_;
            };
        };
    };
};

#endif

