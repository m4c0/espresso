#include "JIT.hpp"

using namespace Espresso::ClassParser;

static bool _test(const char * data, int size, void * result) {
    auto jit = JIT()
        .dataStream(DataStream(data, size))
        .signature("()LTest;");
    if (!jit) return false;

    void * (*fn)() = (void *(*)())jit.buildFunction();
    if (!fn) return false;

    if (fn() != result) return false;

    return true;
}

int main() {
    if (!_test("\x01\xb0", 2, 0)) return 2; // aconst_null; areturn

    return 0;
}

