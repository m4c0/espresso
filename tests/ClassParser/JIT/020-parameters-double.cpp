#include "JIT.hpp"

#include <math.h>

using namespace Espresso::ClassParser;

typedef double (*fn_t)(double, double, double, double);

static bool _test(const char * data, int size, double result, double arg0, double arg1, double arg2, double arg3) {
    auto jit = JIT()
        .dataStream(DataStream(data, size))
        .signature("(DDDD)D");
    if (!jit) return false;

    fn_t fn = (fn_t)jit.buildFunction();
    if (!fn) return false;

    if (fabs(fn(arg0, arg1, arg2, arg3) - result) > 0.0001) return false;

    return true;
}

int main() {
    if (!_test("\x26\xac", 2, 99, 99, 0, 0, 0)) return 1; // dload_0; dreturn
    if (!_test("\x27\xac", 2, 99, 0, 99, 0, 0)) return 1; // dload_1; dreturn
    if (!_test("\x28\xac", 2, 99, 0, 0, 99, 0)) return 1; // dload_2; dreturn
    if (!_test("\x29\xac", 2, 99, 0, 0, 0, 99)) return 1; // dload_3; dreturn

    if (!_test("\x18\0\xac", 3, 99, 99, 0, 0, 0)) return 1; // dload 0; dreturn
    if (!_test("\x18\1\xac", 3, 99, 0, 99, 0, 0)) return 1; // dload 1; dreturn
    if (!_test("\x18\2\xac", 3, 99, 0, 0, 99, 0)) return 1; // dload 2; dreturn
    if (!_test("\x18\3\xac", 3, 99, 0, 0, 0, 99)) return 1; // dload 3; dreturn

    return 0;
}

