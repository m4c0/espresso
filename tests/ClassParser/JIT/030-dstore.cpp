#include "JIT.hpp"

#include <math.h>

using namespace Espresso::ClassParser;

static bool _test(const char * data, int size) {
    auto jit = JIT()
        .dataStream(DataStream(data, size))
        .signature("(D)D");
    if (!jit) return false;

    double (*fn)(double) = (double(*)(double))jit.buildFunction();
    if (!fn) return false;

    if (fabs(fn(99) - 1) > 0.0001) return false;

    return true;
}

int main() {
    if (!_test("\x0f\x47\x26\xaf", 4)) return 1; // dconst_4; dstore_0; dload_0; dreturn
    if (!_test("\x0f\x48\x27\xaf", 4)) return 1; // dconst_4; dstore_1; dload_1; dreturn
    if (!_test("\x0f\x49\x28\xaf", 4)) return 1; // dconst_4; dstore_2; dload_2; dreturn
    if (!_test("\x0f\x4a\x29\xaf", 4)) return 1; // dconst_4; dstore_3; dload_3; dreturn

    if (!_test("\x0f\x39\x09\x18\x09\xaf", 6)) return 1; // dconst_4; dstore 9; dload 9; dreturn
    return 0;
}

