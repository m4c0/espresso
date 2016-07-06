#include "ClassEntry.hpp"

#include "ConstantPool/Utf8.hpp"

using namespace Espresso::ClassParser;

ClassEntry::ClassEntry() {
    message = "Empty class entry";
}

ClassEntry::ClassEntry(ConstantPool::Manager & cpool, DataStream & data) {
    access_ = data.readU16();

    auto name = data.readU16();
    if (!cpool.itemMatchesTag(name, 1)) {
        message = "Invalid entry name";
        return;
    }
    name_ = cpool.itemForIndex<ConstantPool::Utf8>(name);

    auto descriptor = data.readU16();
    if (!cpool.itemMatchesTag(descriptor, 1)) {
        message = "Invalid entry descriptor";
        return;
    }
    descriptor_ = cpool.itemForIndex<ConstantPool::Utf8>(descriptor);

    if (parseAttributes(cpool, data)) {
        message = 0;
    }
}

bool ClassEntry::isAbstract() const {
    return (access_ & 0x0400) != 0;
}
bool ClassEntry::isStatic() const {
    return (access_ & 0x0008) != 0;
}

