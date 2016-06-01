#include "Class.hpp"

#include "Attribute.hpp"
#include "DataStream.hpp"
#include "Field.hpp"
#include "Method.hpp"
#include "ConstantPool/Manager.hpp"

using namespace Espresso::ClassParser;

Class::Class(const char * buffer, int len) {
    auto data = DataStream(buffer, len);

    auto magic = data.readU32();
    if (magic != 0xcafebabe) {
        message = "Invalid magic number";
        return;
    }

    auto minorVersion = data.readU16();
    if (minorVersion != 0) { // Only happened on Java before 1.2
        message = "Class is probably too old (or too new)";
        return;
    }
    auto majorVersion = data.readU16();
    if ((majorVersion < 46) || (majorVersion > 52)) { // We only support Java 1.2 up to 8
        message = "Unsupported class version";
        return;
    }

    auto cpool = ConstantPool::Manager(data);
    if (!cpool) {
        message = cpool.error();
        return;
    }

    auto access = data.readU16();
    if (!access) {
        message = "Invalid access flags";
        return;
    }

    auto thisClass = data.readU16();
    if (!cpool.itemMatchesTag(thisClass, 7)) { // TODO: improve those tag constants
        message = "Invalid class";
        return;
    }

    auto superClass = data.readU16();
    if (!cpool.itemMatchesTag(superClass, 7)) { // TODO: improve those tag constants
        message = "Invalid super class";
        return;
    }

    auto ifaceCount = data.readU16();
    for (int i = 0; i < ifaceCount; i++) {
        auto ifaceIdx = data.readU16();
        if (!cpool.itemMatchesTag(ifaceIdx, 7)) { // TODO: improve those tag constants
            message = "Invalid interface for class";
            return;
        }
    }

    auto fieldCount = data.readU16();
    for (int i = 0; i < fieldCount; i++) {
        auto field = Field(cpool, data);
        if (!field) {
            message = field.error();
            return;
        }
    }

    auto methodCount = data.readU16();
    for (int i = 0; i < methodCount; i++) {
        auto method = Method(cpool, data);
        if (!method) {
            message = method.error();
            return;
        }
    }

    auto attributeCount = data.readU16();
    for (int i = 0; i < attributeCount; i++) {
        auto attribute = Attribute(cpool, data);
        if (!attribute) {
            message = attribute.error();
            return;
        }
    }

    message = 0;
}
Class::~Class() {
}

