#include "Attributed.hpp"

#include "Attribute/Code.hpp"
#include "ConstantPool/Utf8.hpp"

#include <string.h>

using namespace Espresso::ClassParser;

Attributed::~Attributed() {
    if (attributes) delete[] attributes;
}

bool Attributed::parseAttributes(ConstantPool::Manager & cpool, DataStream & data) {
    auto attrCount = data.readU16();

    attributes = new Attribute::Base *[attrCount + 1];
    attributes[attrCount] = 0;

    for (int i = 0; i < attrCount; i++) {
        auto nameIdx = data.readU16();
        if (!cpool.itemMatchesTag(nameIdx, 1)) {
            message = "Invalid attribute name";
            return false;
        }

        auto name = (const char *)cpool.itemForIndex<ConstantPool::Utf8>(nameIdx);

        auto length = data.readU32();
        auto value = data.readBytes(length);
        if (value.reachedEOS()) {
            message = "Invalid attribute length";
            return false;
        }

        if (strcmp(name, "Code") == 0) {
            attributes[i] = new Attribute::Code(cpool, value);
        } else {
            message = "Invalid attribute";
            return false;
        }
    }
    return true;
}

Attribute::Base * Attributed::baseItemForName(const char * name) {
    Attribute::Base ** res = attributes;
    while (*res) {
        auto who = *res;
        if (strcmp(name, who->name()) == 0) break;
        res++;
    }
    return *res;
}

