#include "ClassEntry.hpp"

#include "Attribute.hpp"

using namespace Espresso;

// TODO: Eventually do something with this
ClassEntry::ClassEntry(DataStream & data) {
    auto access = data.readU16();

    auto name = data.readU16();

    auto descriptor = data.readU16();

    auto attrCount = data.readU16();
    for (int i = 0; i < attrCount; i++) {
        auto attr = Attribute(data);
        if (!attr) {
            message = attr.error();
            return;
        }
    }

    message = 0;
}

