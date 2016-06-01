#include "Attribute.hpp"

#include "ConstantPool/Utf8.hpp"

using namespace Espresso::ClassParser;

// TODO: Eventually do something with this
Attribute::Attribute(ConstantPool::Manager & cpool, DataStream & data) {
    auto name = data.readU16();
    if (!cpool.itemMatchesTag(name, 1)) {
        message = "Invalid attribute name";
        return;
    }

    name_ = (const char *)cpool.itemForIndex<ConstantPool::Utf8>(name);

    auto length = data.readU32();
    data_ = data.readBytes(length);
    if (data_.reachedEOS()) {
        message = "Invalid attribute length";
        return;
    }

    message = 0;
}

