#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_FIELDREFINFO_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_FIELDREFINFO_H

#include "DataStream.hpp"
#include "Manager.hpp"
#include "RefInfo.hpp"

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class FieldRefInfo : public RefInfo {
            public:
                FieldRefInfo(Manager & mgr, DataStream & data);
            };
        };
    };
};

#endif

