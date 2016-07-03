#include "JIT.hpp"

#include <math.h>

using namespace Espresso::ClassParser;

static bool _test(const char * data, int size, float result) {
    auto jit = JIT()
        .dataStream(DataStream(data, size))
        .signature("()F");
    if (!jit) return false;

    float (*fn)() = (float(*)())jit.buildFunction();
    if (!fn) return false;

    if (fabsf(fn() - result) > 0.0001) return false;

    return true;
}

int main() {
    if (!_test("\x0b\xae", 2, 0)) return 2; // fconst_0; freturn
    if (!_test("\x0c\xae", 2, 1)) return 3; // fconst_1; freturn
    if (!_test("\x0d\xae", 2, 2)) return 4; // fconst_2; freturn

    return 0;
}

