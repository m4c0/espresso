#include "JIT.hpp"

using namespace Espresso::ClassParser;

int main() {
    // opcodes:
    //     0: a7 00 05 goto +5
    //     3: 05       iconst_2
    //     4: ac       ireturn
    //     5: 04       iconst_1
    //     6: ac       ireturn
    auto jit = JIT()
        .dataStream(DataStream("\xa7\x00\x05\x05\xac\x04\xac", 7))
        .signature("()I");
    if (!jit) return 1;

    auto fn = (int(*)())jit.buildFunction();
    if (!fn) return 2;
    if (fn() != 1) return 3;

    // opcodes:
    //     0: 04       iconst_1
    //     1: a7 00 04 goto +4
    //     4: 05       iconst_2
    //     5: ac       ireturn
    jit.dataStream(DataStream("\x04\xa7\x00\x04\x05\xac", 6));
    if (!jit) return 1;

    fn = (int(*)())jit.buildFunction();
    if (!fn) return 2;
    if (fn() != 1) return 3;
    return 0;
}

