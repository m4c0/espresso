#include "Integer.hpp"

using namespace Espresso::ClassParser::ConstantPool;

Integer::Integer(DataStream & data) : Item(3) {
    auto index = data.readU32();
    value = *(int32_t *)&index; // forcing value to be copied by bits, and not by the "semantic" value
}

