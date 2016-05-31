#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_METHODREFINFO_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_METHODREFINFO_H

#include "DataStream.hpp"
#include "Manager.hpp"
#include "RefInfo.hpp"

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class MethodRefInfo : public RefInfo {
            public:
                MethodRefInfo(Manager & mgr, DataStream & data);
            };
        };
    };
};

#endif

