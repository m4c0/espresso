#include "Method.hpp"

using namespace Espresso::ClassParser;

Method::Method() : ClassEntry() {
}

Method::Method(ConstantPool::Manager & cpool, DataStream & data) : ClassEntry(cpool, data) {
    code_ = itemForName<Attribute::Code>("Code");
}

