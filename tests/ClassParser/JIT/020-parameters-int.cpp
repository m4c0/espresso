#include "JIT.hpp"

using namespace Espresso::ClassParser;

typedef int (*fn_t)(int, int, int, int);

static bool _test(const char * data, int size, int result, int arg0, int arg1, int arg2, int arg3) {
    auto jit = JIT()
        .dataStream(DataStream(data, size))
        .signature("(IIII)I");
    if (!jit) return false;

    fn_t fn = (fn_t)jit.buildFunction();
    if (!fn) return false;

    if (fn(arg0, arg1, arg2, arg3) != result) return false;

    return true;
}

int main() {
    if (!_test("\x1a\xac", 2, 99, 99, 0, 0, 0)) return 1; // iload_0; ireturn
    if (!_test("\x1b\xac", 2, 99, 0, 99, 0, 0)) return 1; // iload_1; ireturn
    if (!_test("\x1c\xac", 2, 99, 0, 0, 99, 0)) return 1; // iload_2; ireturn
    if (!_test("\x1d\xac", 2, 99, 0, 0, 0, 99)) return 1; // iload_3; ireturn

    return 0;
}

