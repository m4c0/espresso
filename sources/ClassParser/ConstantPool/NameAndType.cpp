#include "NameAndType.hpp"

#include "Utf8.hpp"

using namespace Espresso::ClassParser::ConstantPool;

NameAndType::NameAndType(Manager & mgr, DataStream & data) : Item(12) {
    auto nameIdx = data.readU16();
    name_ = mgr[nameIdx];
    if (!name_) {
        message = "Invalid reference to name";
        return;
    }

    auto descriptorIdx = data.readU16();
    descriptor_ = mgr[descriptorIdx];
    if (!descriptor_) {
        message = "Invalid reference to descriptor";
        return;
    }
}

const char * NameAndType::name() const {
    auto utf8 = *(Utf8 **)name_;
    if (!utf8->matchesTag(1)) return 0;
    return *utf8;
}
const char * NameAndType::descriptor() const {
    auto utf8 = *(Utf8 **)descriptor_;
    if (!utf8->matchesTag(1)) return 0;
    return *utf8;
}

