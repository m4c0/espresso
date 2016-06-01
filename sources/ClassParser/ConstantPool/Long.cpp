#include "Long.hpp"

using namespace Espresso::ClassParser::ConstantPool;

Long::Long(DataStream & data) : Item(5) {
    uint64_t a = data.readU32();
    uint64_t b = data.readU32();
    uint64_t ab = (a << 32) | b;
    value = *(int64_t *)&ab; // forcing value to be copied by bits, and not by the "semantic" value
}

