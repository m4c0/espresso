#include "MethodRefInfo.hpp"

using namespace Espresso::ClassParser::ConstantPool;

MethodRefInfo::MethodRefInfo(Manager & mgr, DataStream & data) : RefInfo(mgr, data, 10) {
}

