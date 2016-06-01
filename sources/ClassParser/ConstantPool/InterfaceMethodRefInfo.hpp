#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_INTERFACEMETHODREFINFO_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_INTERFACEMETHODREFINFO_H

#include "DataStream.hpp"
#include "Manager.hpp"
#include "RefInfo.hpp"

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class InterfaceMethodRefInfo : public RefInfo {
            public:
                InterfaceMethodRefInfo(Manager & mgr, DataStream & data);
            };
        };
    };
};

#endif

