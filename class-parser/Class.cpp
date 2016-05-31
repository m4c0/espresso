#include "Class.hpp"

#include "DataStream.hpp"
#include "constant-pool/Manager.hpp"

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
    if (!thisClass || !cpool[thisClass]) { // TODO: check if cpool agrees
        message = "Invalid class";
        return;
    }

    auto superClass = data.readU16();
    if (!superClass || !cpool[superClass]) { // TODO: check if cpool agrees
        message = "Invalid super class";
        return;
    }

    message = 0;
}
Class::~Class() {
}

