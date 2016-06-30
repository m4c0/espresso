#include "ClassInfo.hpp"

#include "Utf8.hpp"

using namespace Espresso::ClassParser::ConstantPool;

ClassInfo::ClassInfo(Manager & mgr, DataStream & data) : Item(7) {
    className_ = data.readU16();
    if (!mgr[className_]) {
        message = "Invalid reference to class name";
    }
}

const char * ClassInfo::className(Manager & mgr) const {
    return mgr.itemForIndex<Utf8>(className_);
}

