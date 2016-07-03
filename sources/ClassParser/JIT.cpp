#include "JIT.hpp"

#include "ConstantPool/MethodRefInfo.hpp"
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
    signature_ = "()V";
    stackSize_ = 65535;
    maxLocals_ = 65535;
    message = 0;
}

JIT & JIT::constantPool(ConstantPool::Manager * cpool) {
    cpool_ = cpool;
    return *this;
}
JIT & JIT::dataStream(DataStream data) {
    data_ = data;
    return *this;
}
JIT & JIT::maxLocals(int locals) {
    maxLocals_ = locals;
    return *this;
}
JIT & JIT::signature(const char * sign) {
    signature_ = sign;
    return *this;
}
JIT & JIT::stackSize(int size) {
    stackSize_ = size;
    return *this;
}

const char * _convert_type(const char * sign, jit_type_t * t) {
    switch (*sign++) {
        case 'I': *t = jit_type_int; break;
        case 'J': *t = jit_type_long; break;
        case 'V': *t = jit_type_void; break;
        default: return 0;
    }
    return sign;
}

jit_type_t _convert_signature(const char * sign) {
    if (*sign != '(') return 0;
    sign++;

    jit_type_t args[1024];
    int argc = 0;
    while (sign && (*sign != 0) && (*sign != ')')) {
        sign = _convert_type(sign, args + argc);
        argc++;
    } 
    if (!sign || (*sign != ')')) return 0;
    sign++;

    jit_type_t ret;
    sign = _convert_type(sign, &ret);
    if (!sign || *sign) return 0;

    return jit_type_create_signature(jit_abi_cdecl, ret, args, argc, 0);
}

void * JIT::buildFunction() const {
    return buildFunction(0);
}
void * JIT::buildFunction(MethodProvider * methods) const {
    jit_context_build_start(_context);

    auto signature = _convert_signature(signature_);
    auto function = jit_function_create(_context, signature);

    auto stack = new jit_value_t[stackSize_];
    auto stackPos = 0; // TODO: Add overrun and underrun checks

    DataStream data = data_;
    while (!data.reachedEOS()) {
        auto opcode = data.readU8();
        switch (opcode) {
            case 0: // nop
                // Just in case some kind of CPU cycle waste is required
                jit_insn_nop(function);
                break;
            case 2: // iconst_m1
            case 3: // iconst_0
            case 4: // iconst_1
            case 5: // iconst_2
            case 6: // iconst_3
            case 7: // iconst_4
            case 8: // iconst_5
                stack[stackPos++] = jit_value_create_nint_constant(function, jit_type_int, opcode - 3);
                break;
            case 9:  // lconst_0
            case 10: // lconst_1
                stack[stackPos++] = jit_value_create_long_constant(function, jit_type_long, opcode - 9);
                break;
            case 16: // bipush
                stack[stackPos++] = jit_value_create_nint_constant(function, jit_type_int, data.readU8());
                break;
            case 172: // ireturn
            case 173: // lreturn
                jit_insn_return(function, stack[--stackPos]);
                break;
            case 177: // return
                jit_insn_default_return(function);
                break;
            case 184: { // invokestatic
                auto index = data.readU16();
                if (!cpool_) {
                    if (Espresso::Log) Espresso::Log("Tried to JIT a invokestatic without a constant pool");
                    return 0;
                }
                if (!methods) {
                    if (Espresso::Log) Espresso::Log("Tried to JIT a invokestatic without a class resolver");
                    return 0;
                }
                if (!cpool_->itemMatchesTag(index, 10)) {
                    if (Espresso::Log) Espresso::Log("Tried to JIT a invokestatic using an invalid constant pool value at %d", index);
                    return 0;
                }
                auto info = cpool_->itemForIndex<ConstantPool::MethodRefInfo>(index);
                auto fn = methods->getNativeMethod(info.className(), info.name(), info.descriptor());
                if (!fn) {
                    if (Espresso::Log) Espresso::Log("Method not found: %s.%s%s", info.className(), info.name(), info.descriptor());
                    return 0;
                }
                auto sign = _convert_signature(info.descriptor());
                auto argc = jit_type_num_params(sign);
                auto args = new jit_value_t[argc];
                for (int i = 0; i < argc; i++) {
                    args[i] = stack[--stackPos];
                }
                stack[stackPos++] = jit_insn_call_native(function, 0, fn, sign, args, argc, JIT_CALL_NOTHROW);
                delete[] args;
                break;
            }
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

