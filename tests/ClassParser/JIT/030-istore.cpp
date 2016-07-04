#include "JIT.hpp"

using namespace Espresso::ClassParser;

static bool _test(const char * data, int size) {
    auto jit = JIT()
        .dataStream(DataStream(data, size))
        .signature("(I)I");
    if (!jit) return false;

    int (*fn)(int) = (int(*)(int))jit.buildFunction();
    if (!fn) return false;

    if (fn(99) != 4) return false;

    return true;
}

int main() {
    if (!_test("\x07\x3b\x1a\xac", 4)) return 1; // iconst_4; istore_0; iload_0; ireturn
    if (!_test("\x07\x3c\x1b\xac", 4)) return 1; // iconst_4; istore_1; iload_1; ireturn
    if (!_test("\x07\x3d\x1c\xac", 4)) return 1; // iconst_4; istore_2; iload_2; ireturn
    if (!_test("\x07\x3e\x1d\xac", 4)) return 1; // iconst_4; istore_3; iload_3; ireturn

    if (!_test("\x07\x36\x09\x15\x09\xac", 6)) return 1; // iconst_4; istore 9; iload 9; ireturn
    return 0;
}

