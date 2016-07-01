#include "RefInfo.hpp"

#include "ClassInfo.hpp"
#include "NameAndType.hpp"

using namespace Espresso::ClassParser::ConstantPool;

RefInfo::RefInfo(Manager & mgr, DataStream & data, int tag) : Item(tag) {
    auto clsIdx = data.readU16();
    classInfo = mgr[clsIdx];
    if (!classInfo) {
        message = "Invalid reference to class info";
        return;
    }

    auto nameTypeIdx = data.readU16();
    nameAndType = mgr[nameTypeIdx];
    if (!nameAndType) {
        message = "Invalid reference to name and type";
        return;
    }
}

const char * RefInfo::className() const {
    const ClassInfo * ci = *(ClassInfo **)classInfo;
    if (!ci->matchesTag(7)) return 0;
    return ci->className();
}
const char * RefInfo::name() const {
    const NameAndType * nt = *(NameAndType **)nameAndType;
    if (!nt->matchesTag(12)) return 0;
    return nt->name();
}
const char * RefInfo::descriptor() const {
    const NameAndType * nt = *(NameAndType **)nameAndType;
    if (!nt->matchesTag(12)) return 0;
    return nt->descriptor();
}

