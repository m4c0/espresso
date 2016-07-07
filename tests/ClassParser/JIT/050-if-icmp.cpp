#include "JIT.hpp"

using namespace Espresso::ClassParser;

int main() {
    // code:
    //     int fn(int a) {
    //         if (a >= 0) {
    //             return 1;
    //         } else {
    //             return 2;
    //         }
    //     }
    //
    // opcodes:
    //     0: 1a       iload_0
    //     1: 03       iconst_0
    //     2: a2 00 05 if_icmpge +5
    //     5: 05       iconst_2
    //     6: ac       ireturn
    //     7: 04       iconst_1
    //     8: ac       ireturn
    auto jit = JIT()
        .dataStream(DataStream("\x1a\x03\xa2\x00\x05\x05\xac\x04\xac", 9))
        .signature("(I)I");
    if (!jit) return 1;

    int (*fn)(int) = (int(*)(int))jit.buildFunction();
    if (!fn) return 2;

    if (fn( 10) != 1) return 3;
    if (fn(  0) != 1) return 3;
    if (fn(-10) != 2) return 4;

    jit.dataStream(DataStream("\x1a\x03\xa0\x00\x05\x05\xac\x04\xac", 9)); // same with ne
    fn = (int(*)(int))jit.buildFunction();
    if (fn(0) != 2) return 5;
    if (fn(1) != 1) return 6;


    return 0;
}

