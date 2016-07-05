#include "JIT.hpp"

#include "Logger.hpp"

#include <iostream>

using namespace Espresso::ClassParser;

static int _test(int i) {
    return i + 6;
}

class MyMethodProvider : public Espresso::ClassParser::MethodProvider {
    virtual void * getNativeMethod(const char * className, const char * name, const char * signature) {
        if (strcmp(className, "Test") != 0) return 0;
        if (strcmp(name, "test") != 0) return 0;
        if (strcmp(signature, "(I)I") != 0) return 0;
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

    auto cpd = DataStream("\0\7" // item count + 1
            "\x0a" "\0\2" "\0\4" // method ref info (10) -> class=2, name/type=4
            "\x07" "\0\3"        // class info (7) -> name=3
            "\x01" "\0\4" "Test" // utf8 (1) -> size=4
            "\x0c" "\0\5" "\0\6" // name/type (12) -> name=5, type=6
            "\x01" "\0\4" "test" // utf8 (1) -> size=4
            "\x01" "\0\4" "(I)I" // utf8 (1) -> size=4
            , 6 * 1 + 9 * 2 + 3 * 4);
    auto cp = Espresso::ClassParser::ConstantPool::Manager(cpd);
    if (!cp) {
        _log("CPool: %s", cp.error());
        return -1;
    }

    auto jit = JIT()
        .constantPool(&cp)
        .dataStream(DataStream("\7\xb8\0\1\xac", 5)) // iconst_4; invokestatic 1; ireturn
        .className("Something")
        .methodName("else")
        .signature("()I");
    if (!jit) return 1;

    auto mr = MyMethodProvider();
    int (*fn)() = (int(*)())jit.buildFunction(&mr);
    if (!fn) return 2;

    if (fn() != 10) return 3;

    return 0;
}
