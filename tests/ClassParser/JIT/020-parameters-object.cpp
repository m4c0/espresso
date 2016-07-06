#include "JIT.hpp"

using namespace Espresso::ClassParser;

typedef void * (*fn_t)(void *, void *, void *, void *);

static bool _test(const char * data, int size, long result, long arg0, long arg1, long arg2, long arg3) {
    auto jit = JIT()
        .dataStream(DataStream(data, size))
        .signature("(LT;LT;LT;LT;)LT;");
    if (!jit) return false;

    fn_t fn = (fn_t)jit.buildFunction();
    if (!fn) return false;

    if (fn((void *)arg0, (void *)arg1, (void *)arg2, (void *)arg3) != (void *)result) return false;

    return true;
}

int main() {
    if (!_test("\x2a\xb0", 2, 99, 99, 0, 0, 0)) return 1; // aload_0; areturn
    if (!_test("\x2b\xb0", 2, 99, 0, 99, 0, 0)) return 1; // aload_1; areturn
    if (!_test("\x2c\xb0", 2, 99, 0, 0, 99, 0)) return 1; // aload_2; areturn
    if (!_test("\x2d\xb0", 2, 99, 0, 0, 0, 99)) return 1; // aload_3; areturn

    if (!_test("\x19\0\xb0", 3, 99, 99, 0, 0, 0)) return 1; // aload 0; areturn
    if (!_test("\x19\1\xb0", 3, 99, 0, 99, 0, 0)) return 1; // aload 1; areturn
    if (!_test("\x19\2\xb0", 3, 99, 0, 0, 99, 0)) return 1; // aload 2; areturn
    if (!_test("\x19\3\xb0", 3, 99, 0, 0, 0, 99)) return 1; // aload 3; areturn

    return 0;
}

