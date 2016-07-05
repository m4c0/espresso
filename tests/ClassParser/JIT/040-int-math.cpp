#include "JIT.hpp"

using namespace Espresso::ClassParser;

static bool _test(const char * data, int size, int a, int b, int res) {
    auto jit = JIT()
        .dataStream(DataStream(data, size))
        .signature("(II)I");
    if (!jit) return false;

    int (*fn)(int, int) = (int(*)(int, int))jit.buildFunction();
    if (!fn) return false;

    if (fn(a, b) != res) return false;

    return true;
}

int main() {
    if (!_test("\x1a\x1b\x64\xac", 4, 15, 5, 10)) return 1; // iload_0; iload_1; isub; ireturn;
    return 0;
}

