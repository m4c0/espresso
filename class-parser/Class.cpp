#include "Class.hpp"
#include "DataStream.hpp"

using namespace Espresso;

Class::Class(const char * buffer, int len) {
    auto data = DataStream(buffer, len);

    this->magic = data.readU32();
    if (this->magic != 0xcafebabe) {
        message = "Invalid magic number";
        return;
    }

    this->minorVersion = data.readU16();
    if (this->minorVersion != 0) { // Only happened on Java before 1.2
        message = "Class is probably too old (or too new)";
        return;
    }
    this->majorVersion = data.readU16();
    if ((this->majorVersion < 46) || (this->majorVersion > 52)) { // We only support Java 1.2 up to 8
        message = "Unsupported class version";
        return;
    }

    message = 0;
}
Class::~Class() {
}

