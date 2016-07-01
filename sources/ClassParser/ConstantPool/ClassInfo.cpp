#include "ClassInfo.hpp"

#include "Utf8.hpp"

using namespace Espresso::ClassParser::ConstantPool;

ClassInfo::ClassInfo(Manager & mgr, DataStream & data) : Item(7) {
    className_ = mgr[data.readU16()];
    if (!className_) {
        message = "Invalid reference to class name";
    }
}

const char * ClassInfo::className() const {
    const Utf8 * utf8 = *(Utf8 **)className_;
    if (!utf8->matchesTag(1)) return 0;
    return *utf8;
}

