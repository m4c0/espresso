#include "JIT.hpp"

using namespace Espresso::ClassParser;

int main() {
    auto jit = JIT().dataStream(DataStream("\x00\x00\x00\xb1", 4)); // nop; nop; nop; return
    if (!jit) return 1;

    void (*fn)() = (void(*)())jit.buildFunction();
    if (!fn) return 2;

    fn(); // Let's just test if it blow up

    return 0;
}
