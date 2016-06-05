#include "Method.hpp"

using namespace Espresso::ClassParser;

Method::Method() {
}

Method::Method(ConstantPool::Manager & cpool, DataStream & data) : ClassEntry(cpool, data) {
}

