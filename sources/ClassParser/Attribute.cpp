#include "Attribute.hpp"

using namespace Espresso;

// TODO: Eventually do something with this
Attribute::Attribute(DataStream & data) {
    auto name = data.readU16();
    auto length = data.readU32();
    const uint8_t * bytes = data.readBytes(length);
    if (!bytes) {
        message = "Invalid attribute";
        return;
    }

    message = 0;
}

