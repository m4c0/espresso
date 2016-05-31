#include "InterfaceMethodRefInfo.hpp"

using namespace Espresso::ClassParser::ConstantPool;

InterfaceMethodRefInfo::InterfaceMethodRefInfo(Manager & mgr, DataStream & data) : RefInfo(mgr, data, 11) {
}

