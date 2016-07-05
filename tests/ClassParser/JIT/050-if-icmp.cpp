#include "JIT.hpp"

using namespace Espresso::ClassParser;

int main() {
    // code:
    //     int fn(int a) {
    //         if (a > 0) {
    //             return 1;
    //         } else {
    //             return 2;
    //         }
    //     }
    //
    // opcodes:
    //     0: iconst_0
    //     1: iload_0
    //     2: if_icmpge +5
    //     5: iconst_1
    //     6: ireturn
    //     7: iconst_2
    //     8: ireturn
    auto jit = JIT()
        .dataStream(DataStream("\x03\x1a\xa2\x00\x05\x04\xac\x05\xac", 9))
        .signature("(I)I");
    if (!jit) return 1;

    int (*fn)(int) = (int(*)(int))jit.buildFunction();
    if (!fn) return 2;

    if (fn( 10) != 2) return 3;
    if (fn(  0) != 2) return 3;
    if (fn(-10) != 1) return 4;

    return 0;
}

