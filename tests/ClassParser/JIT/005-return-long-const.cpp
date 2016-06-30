#include "JIT.hpp"

using namespace Espresso::ClassParser;

static bool _test(const char * data, int size, long result) {
    auto jit = JIT()
        .dataStream(DataStream(data, size))
        .returnType(JIT::Long);
    if (!jit) return false;

    long (*fn)() = (long(*)())jit.buildFunction();
    if (!fn) return false;

    if (fn() != result) return false;

    return true;
}

int main() {
    if (!_test("\x09\xad", 2,  0)) return 2; // iconst_0;  ireturn
    if (!_test("\x0a\xad", 2,  1)) return 3; // iconst_1;  ireturn
}

