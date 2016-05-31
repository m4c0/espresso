#include "Double.hpp"

using namespace Espresso::ClassParser::ConstantPool;

Double::Double(DataStream & data) : Item(6) {
    uint64_t a = data.readU32();
    uint64_t b = data.readU32();
    uint64_t ab = (a << 32) | b;
    value = *(double *)&ab; // forcing value to be copied by bits, and not by the "semantic" value
}

