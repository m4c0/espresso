#include "StringInfo.hpp"

using namespace Espresso::ClassParser::ConstantPool;

// Seriously, why is this a thing?

StringInfo::StringInfo(Manager & mgr, DataStream & data) : Item(8) {
    auto index = data.readU16();
    utf8 = mgr[index];
    if (!utf8) {
        message = "Invalid reference to UTF8";
        return;
    }
}

