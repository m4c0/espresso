#include "Class.hpp"

#include "DataStream.hpp"
#include "Field.hpp"
#include "Method.hpp"
#include "ConstantPool/ClassInfo.hpp"
#include "ConstantPool/Manager.hpp"

#include <stdio.h>

using namespace Espresso::ClassParser;

Class::Class(const char * filename) : cpool_(0) {
    FILE * file = fopen(filename, "r");
    if (!file) {
        message = "File not found";
        return;
    }

    fseek(file, 0, SEEK_END);

    auto size = ftell(file);
    auto buffer = new char[size];

    fseek(file, 0, SEEK_SET);
    if (fread(buffer, 1, size, file) != size) {
        message = "Error reading file";
        return;
    }
    fclose(file);

    loadClass(buffer, size);
    delete buffer;
}

Class::Class(const char * buffer, int len) : cpool_(0) {
    loadClass(buffer, len);
}

void Class::loadClass(const char * buffer, int len) {
    data_ = DataStream(buffer, len, true);

    auto magic = data_.readU32();
    if (magic != 0xcafebabe) {
        message = "Invalid magic number";
        return;
    }

    auto minorVersion = data_.readU16();
    if (minorVersion != 0) { // Only happened on Java before 1.2
        message = "Class is probably too old (or too new)";
        return;
    }
    auto majorVersion = data_.readU16();
    if ((majorVersion < 46) || (majorVersion > 52)) { // We only support Java 1.2 up to 8
        message = "Unsupported class version";
        return;
    }

    cpool_ = new ConstantPool::Manager(data_);
    ConstantPool::Manager & cpool = *cpool_;
    if (!cpool) {
        message = cpool.error();
        return;
    }

    auto access = data_.readU16();
    if (!access) {
        message = "Invalid access flags";
        return;
    }

    auto thisClass = data_.readU16();
    if (!cpool.itemMatchesTag(thisClass, 7)) { // TODO: improve those tag constants
        message = "Invalid class";
        return;
    }

    auto classInfo = cpool.itemForIndex<ConstantPool::ClassInfo>(thisClass);
    name_ = classInfo.className(cpool);
    if (!name_) {
        message = "Invalid class name at class info";
        return;
    }

    auto superClass = data_.readU16();
    if (!cpool.itemMatchesTag(superClass, 7)) { // TODO: improve those tag constants
        message = "Invalid super class";
        return;
    }

    auto ifaceCount = data_.readU16();
    for (int i = 0; i < ifaceCount; i++) {
        auto ifaceIdx = data_.readU16();
        if (!cpool.itemMatchesTag(ifaceIdx, 7)) { // TODO: improve those tag constants
            message = "Invalid interface for class";
            return;
        }
    }

    auto fieldCount = data_.readU16();
    for (int i = 0; i < fieldCount; i++) {
        auto field = Field(cpool, data_);
        if (!field) {
            message = field.error();
            return;
        }
    }

    auto methodCount = data_.readU16();
    methods_ = new Method[methodCount + 1]; // Last one works as a "end" marker
    for (int i = 0; i < methodCount; i++) {
        methods_[i] = Method(cpool, data_);
        if (!methods_[i]) {
            message = methods_[i].error();
            return;
        }
    }

    if (parseAttributes(cpool, data_)) {
        message = 0;
    }
}
Class::~Class() {
    if (cpool_) delete cpool_;
}

