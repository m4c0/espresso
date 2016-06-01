#include "Float.hpp"

using namespace Espresso::ClassParser::ConstantPool;

Float::Float(DataStream & data) : Item(4) {
    auto index = data.readU32();
    value = *(float *)&index; // forcing value to be copied by bits, and not by the "semantic" value
}

