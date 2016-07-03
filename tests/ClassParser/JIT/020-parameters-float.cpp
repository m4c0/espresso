#include "JIT.hpp"

#include <math.h>

using namespace Espresso::ClassParser;

typedef float (*fn_t)(float, float, float, float);

static bool _test(const char * data, int size, float result, float arg0, float arg1, float arg2, float arg3) {
    auto jit = JIT()
        .dataStream(DataStream(data, size))
        .signature("(FFFF)F");
    if (!jit) return false;

    fn_t fn = (fn_t)jit.buildFunction();
    if (!fn) return false;

    if (fabsf(fn(arg0, arg1, arg2, arg3) - result) > 0.0001) return false;

    return true;
}

int main() {
    if (!_test("\x22\xac", 2, 99, 99, 0, 0, 0)) return 1; // fload_0; freturn
    if (!_test("\x23\xac", 2, 99, 0, 99, 0, 0)) return 1; // fload_1; freturn
    if (!_test("\x24\xac", 2, 99, 0, 0, 99, 0)) return 1; // fload_2; freturn
    if (!_test("\x25\xac", 2, 99, 0, 0, 0, 99)) return 1; // fload_3; freturn

    if (!_test("\x17\0\xac", 3, 99, 99, 0, 0, 0)) return 1; // fload 0; freturn
    if (!_test("\x17\1\xac", 3, 99, 0, 99, 0, 0)) return 1; // fload 1; freturn
    if (!_test("\x17\2\xac", 3, 99, 0, 0, 99, 0)) return 1; // fload 2; freturn
    if (!_test("\x17\3\xac", 3, 99, 0, 0, 0, 99)) return 1; // fload 3; freturn

    return 0;
}

