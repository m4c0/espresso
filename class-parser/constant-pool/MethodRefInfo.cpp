#include "MethodRefInfo.hpp"

using namespace Espresso::ClassParser::ConstantPool;

MethodRefInfo::MethodRefInfo(Manager & mgr, DataStream & data) : Item(10) {
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

