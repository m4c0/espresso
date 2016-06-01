#include "Attribute.hpp"

using namespace Espresso::ClassParser;

// TODO: Eventually do something with this
Attribute::Attribute(ConstantPool::Manager & cpool, DataStream & data) {
    auto name = data.readU16();
    auto length = data.readU32();
    const uint8_t * bytes = data.readBytes(length);
    if (!bytes) {
        message = "Invalid attribute";
        return;
    }

    message = 0;
}

