#include "JIT.hpp"

#include <math.h>

using namespace Espresso::ClassParser;

static bool _test(const char * data, int size, double result) {
    auto jit = JIT()
        .dataStream(DataStream(data, size))
        .signature("()D");
    if (!jit) return false;

    double (*fn)() = (double(*)())jit.buildFunction();
    if (!fn) return false;

    if (fabs(fn() - result) > 0.0001) return false;

    return true;
}

int main() {
    if (!_test("\x0e\xaf", 2, 0)) return 2; // dconst_0; dreturn
    if (!_test("\x0f\xaf", 2, 1)) return 3; // dconst_1; dreturn

    return 0;
}

