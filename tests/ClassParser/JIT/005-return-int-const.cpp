#include "JIT.hpp"

using namespace Espresso::ClassParser;

int main() {
    auto jit = JIT().dataStream(DataStream("\x05\xac", 2)); // iconst_2; ireturn
    if (!jit) return 1;

    int (*fn)() = (int(*)())jit.buildFunction();
    if (!fn) return 2;

    if (fn() != 2) return 3;

    return 0;
}

