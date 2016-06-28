#include "Code.hpp"

using namespace Espresso::ClassParser::Attribute;

Code::Code() : Base() {
    message = "Empty code";
}
Code::Code(ConstantPool::Manager & cpool, DataStream & data) : Base("Code") {
    code_.stackSize(data.readU16());
    code_.maxLocals(data.readU16());

    auto length = data.readU32();
    auto codeBytes = data.readBytes(length);
    if (codeBytes.reachedEOS()) {
        message = "Invalid code length";
        return;
    }
    code_.dataStream(codeBytes);

    length = data.readU32();
    data.readBytes(length * 8); // Just shamelessly skip the exception table for now

    if (!parseAttributes(cpool, data)) return;

    message = 0;
}

