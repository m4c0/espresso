#include "JIT.hpp"

using namespace Espresso::ClassParser;

int main() {
    // code:
    //     int fn(object a) {
    //         if (a == null) {
    //             return 1;
    //         } else {
    //             return 2;
    //         }
    //     }
    //
    // opcodes:
    //     0: 2a       aload_0
    //     1: c6 00 05 ifnull +5
    //     4: 05       iconst_2
    //     5: ac       ireturn
    //     6: 04       iconst_1
    //     7: ac       ireturn
    auto jit = JIT()
        .dataStream(DataStream("\x2a\xc6\x00\x05\x05\xac\x04\xac", 8))
        .signature("(LTest;)I");
    if (!jit) return 1;

    auto fn = (int(*)(void *))jit.buildFunction();
    if (!fn) return 2;

    if (fn((void *) 0) != 1) return 3;
    if (fn((void *) 1) != 2) return 4;

    jit.dataStream(DataStream("\x2a\xc7\x00\x05\x05\xac\x04\xac", 8)); // same with ne
    fn = (int(*)(void *))jit.buildFunction();
    if (!fn) return 5;

    if (fn((void *) 0) != 2) return 6;
    if (fn((void *) 1) != 1) return 7;

    return 0;
}

