#include "Attributed.hpp"

#include "Attribute.hpp"

#include <string.h>

using namespace Espresso::ClassParser;

bool Attributed::parseAttributes(ConstantPool::Manager & cpool, DataStream & data) {
    auto attrCount = data.readU16();
    for (int i = 0; i < attrCount; i++) {
        auto attr = Attribute(cpool, data);
        if (!attr) {
            message = attr.error();
            return false;
        }
        if (strcmp(attr.name(), "Code") == 0) {
            code_ = attr.data();
        }
    }
    return true;
}

