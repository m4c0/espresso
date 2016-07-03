#include "JIT.hpp"

using namespace Espresso::ClassParser;

typedef long (*fn_t)(long, long, long, long);

static bool _test(const char * data, int size, long result, long arg0, long arg1, long arg2, long arg3) {
    auto jit = JIT()
        .dataStream(DataStream(data, size))
        .signature("(JJJJ)J");
    if (!jit) return false;

    fn_t fn = (fn_t)jit.buildFunction();
    if (!fn) return false;

    if (fn(arg0, arg1, arg2, arg3) != result) return false;

    return true;
}

int main() {
    if (!_test("\x1e\xac", 2, 99, 99, 0, 0, 0)) return 1; // lload_0; lreturn
    if (!_test("\x1f\xac", 2, 99, 0, 99, 0, 0)) return 1; // lload_1; lreturn
    if (!_test("\x20\xac", 2, 99, 0, 0, 99, 0)) return 1; // lload_2; lreturn
    if (!_test("\x21\xac", 2, 99, 0, 0, 0, 99)) return 1; // lload_3; lreturn

    if (!_test("\x16\0\xac", 3, 99, 99, 0, 0, 0)) return 1; // lload 0; lreturn
    if (!_test("\x16\1\xac", 3, 99, 0, 99, 0, 0)) return 1; // lload 1; lreturn
    if (!_test("\x16\2\xac", 3, 99, 0, 0, 99, 0)) return 1; // lload 2; lreturn
    if (!_test("\x16\3\xac", 3, 99, 0, 0, 0, 99)) return 1; // lload 3; lreturn

    return 0;
}

