#include "ClassInfo.hpp"

using namespace Espresso::ClassParser::ConstantPool;

ClassInfo::ClassInfo(Manager & mgr, DataStream & data) : Item(7) {
    auto clsNameIdx = data.readU16();
    className = mgr[clsNameIdx];
    if (!className) {
        message = "Invalid reference to class name";
    }
}

