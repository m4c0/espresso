#include "JIT.hpp"

#include "Logger.hpp"

#include <jit/jit.h>
#include <jit/jit-dump.h>
#include <stdio.h>

using namespace Espresso::ClassParser;

static jit_context_t _context;

static __attribute__((constructor)) void _initialize_libjit() {
    _context = jit_context_create();
}
static __attribute__((destructor)) void _cleanup_libjit() {
    jit_context_destroy(_context);
}

JIT::JIT() {
    returnType_ = Void;
    stackSize_ = 65535;
    maxLocals_ = 65535;
    message = 0;
}

JIT & JIT::dataStream(DataStream data) {
    data_ = data;
    return *this;
}
JIT & JIT::maxLocals(int locals) {
    maxLocals_ = locals;
    return *this;
}
JIT & JIT::returnType(Type type) {
    returnType_ = type;
    return *this;
}
JIT & JIT::stackSize(int size) {
    stackSize_ = size;
    return *this;
}

void * JIT::buildFunction() const {
    jit_context_build_start(_context);

    jit_type_t ret;
    switch (returnType_) {
        case Void: ret = jit_type_void; break;
        case Int:  ret = jit_type_int; break;
    }

    auto signature = jit_type_create_signature(jit_abi_cdecl, ret, 0, 0, 0);
    auto function = jit_function_create(_context, signature);

    auto stack = new jit_value_t[stackSize_];
    auto stackPos = 0; // TODO: Add overrun and underrun checks

    DataStream data = data_;
    while (!data.reachedEOS()) {
        auto opcode = data.readU8();
        switch (opcode) {
            case 2: // iconst_m1
            case 3: // iconst_0
            case 4: // iconst_1
            case 5: // iconst_2
            case 6: // iconst_3
            case 7: // iconst_4
            case 8: // iconst_5
                stack[stackPos++] = jit_value_create_nint_constant(function, jit_type_nint, opcode - 3);
                break;
            case 172: // ireturn
                jit_insn_return(function, stack[--stackPos]);
                break;
            case 177: // return
                jit_insn_default_return(function);
                break;
            default:
                if (Espresso::Log) Espresso::Log("Unknown opcode: %02x", opcode);

                //jit_context_build_end(_context);
                //message = "Unknown/unsupported opcode";
                //return 0;
        }
    }

#warning "do a '#if DEBUG' or something"
    jit_dump_function(stderr, function, 0);
    jit_function_compile(function);
    jit_context_build_end(_context);

    return jit_function_to_closure(function);
}

