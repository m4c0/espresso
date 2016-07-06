#include "JIT.hpp"

using namespace Espresso::ClassParser;

int main() {
    auto jit = JIT()
        .dataStream(DataStream("\x1b\xac", 2)) // iload_1; ireturn;
        .className("Test")
        .methodName("test")
        .signature("(II)I");

    auto fn = (int(*)(int, int))jit.buildFunction();
    if (!fn) return 1;
    if (fn(0, 99) != 99) return 2;

    auto ijit = jit.instanceMethod(true);
    auto ifn = (int(*)(void *, int, int))ijit.buildFunction();
    if (!ifn) return 3;
    if (ifn(0, 99, 0) != 99) return 3;

    return 0;
}

