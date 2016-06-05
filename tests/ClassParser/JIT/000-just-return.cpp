#include "JIT.hpp"

using namespace Espresso::ClassParser;

int main() {
    auto jit = JIT().dataStream(DataStream("\xb1", 1));
    if (!jit) return 1;

    void (*fn)() = (void(*)())jit.buildFunction();
    if (!fn) return 2;

    fn(); // Let's just test if it blow up

    return 0;
}
