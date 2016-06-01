#include "ClassEntry.hpp"

using namespace Espresso::ClassParser;

// TODO: Eventually do something with this
ClassEntry::ClassEntry(ConstantPool::Manager & cpool, DataStream & data) {
    auto access = data.readU16();

    auto name = data.readU16();

    auto descriptor = data.readU16();

    if (parseAttributes(cpool, data)) {
        message = 0;
    }
}

