#include "JIT.hpp"

using namespace Espresso::ClassParser;

int main() {
    JIT jit(DataStream("\xb1", 1));
    if (!jit) return 1;

    void (*fn)() = (void(*)())jit.createFunction();
    if (!fn) return 2;

    fn(); // Let's just test if it blow up

    return 0;
}
