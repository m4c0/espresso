#include "FieldRefInfo.hpp"

using namespace Espresso::ClassParser::ConstantPool;

FieldRefInfo::FieldRefInfo(Manager & mgr, DataStream & data) : RefInfo(mgr, data, 9) {
}

