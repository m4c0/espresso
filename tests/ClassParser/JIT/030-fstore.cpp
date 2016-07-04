#include "JIT.hpp"

#include <math.h>

using namespace Espresso::ClassParser;

static bool _test(const char * data, int size) {
    auto jit = JIT()
        .dataStream(DataStream(data, size))
        .signature("(F)F");
    if (!jit) return false;

    float (*fn)(float) = (float(*)(float))jit.buildFunction();
    if (!fn) return false;

    if (fabsf(fn(99) - 1) > 0.0001) return false;

    return true;
}

int main() {
    if (!_test("\x0c\x43\x22\xae", 4)) return 1; // fconst_4; fstore_0; fload_0; freturn
    if (!_test("\x0c\x44\x23\xae", 4)) return 1; // fconst_4; fstore_1; fload_1; freturn
    if (!_test("\x0c\x45\x24\xae", 4)) return 1; // fconst_4; fstore_2; fload_2; freturn
    if (!_test("\x0c\x46\x25\xae", 4)) return 1; // fconst_4; fstore_3; fload_3; freturn

    if (!_test("\x0c\x38\x09\x17\x09\xae", 6)) return 1; // fconst_4; fstore 9; fload 9; freturn
    return 0;
}

