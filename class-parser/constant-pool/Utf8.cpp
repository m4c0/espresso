#include "Utf8.hpp"

using namespace Espresso::ClassParser::ConstantPool;

Utf8::Utf8(DataStream & data) : Item(1), value(0) {
    auto length = data.readU16();
    auto utf8 = new char[length + 1];
    for (int i = 0; i < length; i++) {
        if (data.reachedEOS()) {
            message = "Truncated string on constant pool";
            return;
        }
        utf8[i] = data.readU8();
    }
    utf8[length] = 0;
    value = utf8;
}
Utf8::~Utf8() {
    if (value) delete value;
}

