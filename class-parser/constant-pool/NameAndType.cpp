#include "NameAndType.hpp"

using namespace Espresso::ClassParser::ConstantPool;

NameAndType::NameAndType(Manager & mgr, DataStream & data) : Item(12) {
    auto nameIdx = data.readU16();
    name = mgr[nameIdx];
    if (!name) {
        message = "Invalid reference to name";
        return;
    }

    auto descriptorIdx = data.readU16();
    descriptor = mgr[descriptorIdx];
    if (!descriptor) {
        message = "Invalid reference to descriptor";
        return;
    }
}

