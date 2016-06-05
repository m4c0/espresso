#include "JIT.hpp"

using namespace Espresso::ClassParser;

JIT::JIT(DataStream data) {
    message = 0;
}

// Mini-challenge for today: what's the minimal step to make this fail
// the test, since it's almost the same result (opcode-wise) as the JIT
// of the class' <init>
static void _dummy() {}
void * JIT::createFunction() {
    return (void *)_dummy;
}

