#include "Class.hpp"

#include "DataStream.hpp"
#include "Field.hpp"
#include "Method.hpp"
#include "ConstantPool/Manager.hpp"

using namespace Espresso::ClassParser;

#if USE_CPP_STL
Class::Class(const char * filename) {
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    loadClass(in);
}
Class::Class(std::string filename) {
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    loadClass(in);
}
Class::Class(std::ifstream & in) {
    loadClass(in);
}

void Class::loadClass(std::ifstream & in) {
    if (!in) {
        message = "File not found";
        return;
    }

    in.seekg(0, std::ios::end);
    auto size = in.tellg();

    auto buffer = new char[size];
    in.seekg(0, std::ios::beg);
    in.read(buffer, size);
    loadClass(buffer, size);
    delete buffer;
}
#endif

Class::Class(const char * buffer, int len) {
    loadClass(buffer, len);
}

void Class::loadClass(const char * buffer, int len) {
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
    methods_ = new Method[methodCount + 1]; // Last one works as a "end" marker
    for (int i = 0; i < methodCount; i++) {
        methods_[i] = Method(cpool, data);
        if (!methods_[i]) {
            message = methods_[i].error();
            return;
        }
    }

    if (parseAttributes(cpool, data)) {
        message = 0;
    }
}

