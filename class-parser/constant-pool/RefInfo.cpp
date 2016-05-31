#include "RefInfo.hpp"

using namespace Espresso::ClassParser::ConstantPool;

RefInfo::RefInfo(Manager & mgr, DataStream & data, int tag) : Item(tag) {
    auto clsNameIdx = data.readU16();
    className = mgr[clsNameIdx];
    if (!className) {
        message = "Invalid reference to class name";
        return;
    }

    auto nameTypeIdx = data.readU16();
    nameAndType = mgr[nameTypeIdx];
    if (!nameAndType) {
        message = "Invalid reference to name and type";
        return;
    }
}

