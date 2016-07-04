#include "JIT.hpp"

using namespace Espresso::ClassParser;

static bool _test(const char * data, int size) {
    auto jit = JIT()
        .dataStream(DataStream(data, size))
        .signature("(J)J");
    if (!jit) return false;

    long (*fn)(long) = (long(*)(long))jit.buildFunction();
    if (!fn) return false;

    if (fn(99) != 1) return false;

    return true;
}

int main() {
    if (!_test("\x0a\x3f\x1e\xad", 4)) return 1; // lconst_1; lstore_0; lload_0; lreturn
    if (!_test("\x0a\x40\x1f\xad", 4)) return 1; // lconst_1; lstore_1; lload_1; lreturn
    if (!_test("\x0a\x41\x20\xad", 4)) return 1; // lconst_1; lstore_2; lload_2; lreturn
    if (!_test("\x0a\x42\x21\xad", 4)) return 1; // lconst_1; lstore_3; lload_3; lreturn

    if (!_test("\x0a\x37\x09\x16\x09\xad", 6)) return 1; // lconst_1; lstore 9; lload 9; lreturn
    return 0;
}

