#include "JIT.hpp"

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

JIT::JIT(DataStream data) : JIT(data, 256) {
}

JIT::JIT(DataStream data, int stackSize) {
    jit_context_build_start(_context);

    auto signature = jit_type_create_signature(jit_abi_cdecl, jit_type_int, 0, 0, 0);
    auto function = jit_function_create(_context, signature);

    auto stack = new jit_value_t[stackSize];
    auto stackPos = 0; // TODO: Add overrun and underrun checks

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
        }
    }

    jit_dump_function(stderr, function, 0);
    jit_function_compile(function);
    jit_context_build_end(_context);

    function_ = jit_function_to_closure(function);
    message = 0;
}

