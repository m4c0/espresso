#include "JIT.hpp"

#include "Logger.hpp"

#include <iostream>

using namespace Espresso::ClassParser;

JIT jit;

class MyMethodProvider : public Espresso::ClassParser::MethodProvider {
    virtual void * getNativeMethod(const char * className, const char * name, const char * signature) {
        return jit.buildFunction(this);
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

    // if (a < 0) return 0;
    // return fn(a - 1) - 1

    // 0:  iload_0
    // 1:  iconst_0
    // 2:  if_icmpge +5
    // 5:  iconst_0
    // 6:  ireturn
    // 7:  iload_0
    // 8:  iconst_1
    // 9:  isub
    // 10: invokestatic 1
    // 13: iconst_1
    // 14: isub
    // 15: ireturn
    jit = JIT()
        .constantPool(&cp)
        .dataStream(DataStream("\x1a\x03\xa2\x00\x05\x03\xac\x1a\x04\x64\xb8\x00\x01\x04\x64\xac", 16))
        .className("Test")
        .methodName("test")
        .signature("(I)I");
    if (!jit) return 1;

    auto mr = MyMethodProvider();
    int (*fn)(int) = (int(*)(int))jit.buildFunction(&mr);
    if (!fn) return 2;

    if (fn(5) != -6) return 3;
    if (fn(3) != -4) return 4;

    // TODO: Test for looped recursion (a calls b, b calls a)
    return 0;
}
