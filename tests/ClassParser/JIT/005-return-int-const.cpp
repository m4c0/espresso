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
    if (!_test("\x02\xac", 2, -1)) return 1; // iconst_m1; ireturn
    if (!_test("\x03\xac", 2,  0)) return 2; // iconst_0;  ireturn
    if (!_test("\x04\xac", 2,  1)) return 3; // iconst_1;  ireturn
    if (!_test("\x05\xac", 2,  2)) return 4; // iconst_2;  ireturn
    if (!_test("\x06\xac", 2,  3)) return 5; // iconst_3;  ireturn
    if (!_test("\x07\xac", 2,  4)) return 6; // iconst_4;  ireturn
    if (!_test("\x08\xac", 2,  5)) return 7; // iconst_5;  ireturn

    if (!_test("\x10\x63\xac", 3, 99)) return 8; // bipush 99; ireturn
    if (!_test("\x11\x00\x63\xac", 4, 99)) return 9; // sipush 99; ireturn

    return 0;
}

