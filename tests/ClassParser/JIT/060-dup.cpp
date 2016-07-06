#include "JIT.hpp"

using namespace Espresso::ClassParser;

static bool _test(const char * data, int size, int result) {
    auto jit = JIT()
        .dataStream(DataStream(data, size))
        .signature("()I");
    if (!jit) return false;

    int (*fn)() = (int(*)())jit.buildFunction();
    if (!fn) return false;

    if (fn() != result) return false;

    return true;
}

int main() {
    if (!_test("\x08\x59\x60\xac", 4, 10)) return 7; // iconst_5; dup; iadd; ireturn

    return 0;
}

