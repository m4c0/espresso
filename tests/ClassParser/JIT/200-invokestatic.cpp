#include "JIT.hpp"

#include "Logger.hpp"

#include <iostream>

using namespace Espresso::ClassParser;

static int _test(int i, int x) {
    return (i << 8) | x;
}

class MyMethodProvider : public Espresso::ClassParser::MethodProvider {
    virtual void * getNativeMethod(const char * className, const char * name, const char * signature) {
        if (strcmp(className, "Test") != 0) return 0;
        if (strcmp(name, "test") != 0) return 0;
        if (strcmp(signature, "(II)I") != 0) return 0;
        return (void *)_test;
    }
};

void _log(const char * fmt, ...) {
    va_list va;
    va_start(va, fmt);
    vfprintf(stderr, fmt, va);
    va_end(va);

    std::cerr << std::endl;
}

int main() {
    Espresso::Log = _log;

    auto cpd = DataStream("\0\7"  // 2 - item count + 1
            "\x0a" "\0\2" "\0\4"  // 5 - method ref info (10) -> class=2, name/type=4
            "\x07" "\0\3"         // 3 - class info (7) -> name=3
            "\x01" "\0\4" "Test"  // 7 - utf8 (1) -> size=4
            "\x0c" "\0\5" "\0\6"  // 5 - name/type (12) -> name=5, type=6
            "\x01" "\0\4" "test"  // 7 - utf8 (1) -> size=4
            "\x01" "\0\5" "(II)I" // 8 - utf8 (1) -> size=4
            , 37);
    auto cp = Espresso::ClassParser::ConstantPool::Manager(cpd);
    if (!cp) {
        _log("CPool: %s", cp.error());
        return -1;
    }

    auto jit = JIT()
        .constantPool(&cp)
        .dataStream(DataStream("\x07\x04\xb8\0\1\xac", 6)) // iconst_4; iconst_1; invokestatic 1; ireturn
        .className("Something")
        .methodName("else")
        .signature("()I");
    if (!jit) return 1;

    auto mr = MyMethodProvider();

    int (*fn)() = (int(*)())jit.buildFunction(&mr);
    if (!fn) return 2;
    if (fn() != 0x0401) return 3;

    jit.instanceMethod(true)
        .dataStream(DataStream("\x2a\x07\x04\xb6\x00\x01\xac", 6)); // aload_0; iconst_4; iconst_1; invokevirtual 1; ireturn
    if (!jit) return 4;

    auto fn2 = (int(*)(void *))jit.buildFunction(&mr);
    if (!fn2) return 5;
    if (fn2((void *)0x99) != 0x9904) return 6;

    return 0;
}
