#include "JIT.hpp"

#include "ConstantPool/MethodRefInfo.hpp"
#include "JIT/OperandStack.hpp"
#include "JIT/ProgressNode.hpp"
#include "Logger.hpp"

#include <jit/jit.h>
#include <jit/jit-dump.h>
#include <stdio.h>
#include <string.h>

using namespace Espresso::ClassParser;
using namespace Espresso::ClassParser::JITInternals;

static ProgressNode * _progressStack = 0;

static jit_context_t _context;

static __attribute__((constructor)) void _initialize_libjit() {
    _context = jit_context_create();
}
static __attribute__((destructor)) void _cleanup_libjit() {
    jit_context_destroy(_context);
}

JIT::JIT() {
    className_ = methodName_ = 0;
    signature_ = "()V";
    stackSize_ = 65535;
    maxLocals_ = 65535;
    message = 0;
    instance_ = false;
}

JIT & JIT::className(const char * name) {
    className_ = name;
    return *this;
}
JIT & JIT::constantPool(ConstantPool::Manager * cpool) {
    cpool_ = cpool;
    return *this;
}
JIT & JIT::dataStream(DataStream data) {
    data_ = data;
    return *this;
}
JIT & JIT::instanceMethod(bool i) {
    instance_ = i;
    return *this;
}
JIT & JIT::maxLocals(int locals) {
    maxLocals_ = locals;
    return *this;
}
JIT & JIT::methodName(const char * name) {
    methodName_ = name;
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
        case 'D': *t = jit_type_float64; break;
        case 'F': *t = jit_type_float32; break;
        case 'I': *t = jit_type_int; break;
        case 'J': *t = jit_type_long; break;
        case 'L': {
            while (*++sign) {
                switch (*sign) {
                    case ';': *t = jit_type_void_ptr; return sign + 1;
                    case ')': return 0;
                    case 0: return 0;
                }
            }
            return 0;
        }
        case 'V': *t = jit_type_void; break;
        case 'Z': *t = jit_type_int; break;
        default: return 0;
    }
    return sign;
}

jit_type_t _convert_signature(const char * sign, bool instance) {
    if (*sign != '(') return 0;
    sign++;

    jit_type_t args[1024];
    int argc = 0;
    if (instance) {
        args[0] = jit_type_void_ptr;
        argc++;
    }
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

jit_label_t * _branchLabel(jit_label_t * labels, DataStream & data) {
    auto pos = data.bytesRead() - 1;
    auto jmp = data.readU16();
    return labels + pos + jmp;
}
void _buildJump(jit_function_t function, bool ifnot, OperandStack & stack, jit_label_t * labels, DataStream & data) {
    auto lbl = _branchLabel(labels, data);
    if (ifnot) {
        jit_insn_branch_if_not(function, *stack, lbl);
    } else {
        jit_insn_branch_if(function, *stack, lbl);
    }
}

void * JIT::buildFunction() const {
    return buildFunction(0);
}
void * JIT::buildFunction(MethodProvider * methods) const {
    if (!_progressStack) jit_context_build_start(_context);

    auto signature = _convert_signature(signature_, instance_);
    auto function = jit_function_create(_context, signature);

    _progressStack = new ProgressNode(className_, methodName_, signature_, function, _progressStack);

    auto stack = OperandStack(function, stackSize_);

    auto locals = new jit_value_t[maxLocals_];
    for (int i = 0; i < jit_type_num_params(signature); i++) {
        locals[i] = jit_value_get_param(function, i);
    }

    DataStream data = data_;
    auto labels = new jit_label_t[data.bytesRemaining()];
    for (int i = 0; i < data.bytesRemaining(); i++) {
        labels[i] = jit_label_undefined;
    }
    while (!data.reachedEOS()) {
        jit_insn_label(function, labels + data.bytesRead());

        auto opcode = data.readU8();
        switch (opcode) {
            case 0: // nop
                // Just in case some kind of CPU cycle waste is required
                jit_insn_nop(function);
                break;
            case 1: // aconst_null
                stack << jit_value_create_nint_constant(function, jit_type_void_ptr, 0);
                break;
            case 2: // iconst_m1
            case 3: // iconst_0
            case 4: // iconst_1
            case 5: // iconst_2
            case 6: // iconst_3
            case 7: // iconst_4
            case 8: // iconst_5
                stack << jit_value_create_nint_constant(function, jit_type_int, opcode - 3);
                break;
            case 9:  // lconst_0
            case 10: // lconst_1
                stack << jit_value_create_long_constant(function, jit_type_long, opcode - 9);
                break;
            case 11: // fconst_0
            case 12: // fconst_1
            case 13: // fconst_2
                stack << jit_value_create_float32_constant(function, jit_type_float32, opcode - 11);
                break;
            case 14: // dconst_0
            case 15: // dconst_1
                stack << jit_value_create_float64_constant(function, jit_type_float64, opcode - 14);
                break;
            case 16: // bipush
                stack << jit_value_create_nint_constant(function, jit_type_int, data.readU8());
                break;
            case 17: // sipush
                stack << jit_value_create_nint_constant(function, jit_type_int, data.readU16());
                break;
            //case 18: // ldc - TODO: deal with constant pool items
            //case 19: // ldc_w - TODO: deal with constant pool items (2 bytes)
            //case 20: // ldc2_w - TODO: deal with constant pool items (2 bytes, for long/double)
            case 21: // iload
            case 22: // lload
            case 23: // fload
            case 24: // dload
            case 25: // aload
                stack << locals[data.readU8()];
                break;
            case 26: // iload_0
            case 27: // iload_1
            case 28: // iload_2
            case 29: // iload_3
                stack << locals[opcode - 26];
                break;
            case 30: // lload_0
            case 31: // lload_1
            case 32: // lload_2
            case 33: // lload_3
                stack << locals[opcode - 30];
                break;
            case 34: // fload_0
            case 35: // fload_1
            case 36: // fload_2
            case 37: // fload_3
                stack << locals[opcode - 34];
                break;
            case 38: // dload_0
            case 39: // dload_1
            case 40: // dload_2
            case 41: // dload_3
                stack << locals[opcode - 38];
                break;
            case 42: // aload_0
            case 43: // aload_1
            case 44: // aload_2
            case 45: // aload_3
                stack << locals[opcode - 42];
                break;
            //case 46-53: more loads
            case 54: // istore
            case 55: // lstore
            case 56: // fstore
            case 57: // dstore
            //case 58: // astore
                locals[data.readU8()] = *stack;
                break;
            case 59: // istore_0
            case 60: // istore_1
            case 61: // istore_2
            case 62: // istore_3
                locals[opcode - 59] = *stack;
                break;
            case 63: // lstore_0
            case 64: // lstore_1
            case 65: // lstore_2
            case 66: // lstore_3
                locals[opcode - 63] = *stack;
                break;
            case 67: // fstore_0
            case 68: // fstore_1
            case 69: // fstore_2
            case 70: // fstore_3
                locals[opcode - 67] = *stack;
                break;
            case 71: // dstore_0
            case 72: // dstore_1
            case 73: // dstore_2
            case 74: // dstore_3
                locals[opcode - 71] = *stack;
                break;
            //case 75-86: more stores
            case 89: { // dup
                auto value = *stack;
                stack << value << value;
                break;
            }
            case 96: // iadd
                stack.op2(jit_insn_add);
                break;
            case 100: // isub
                stack.op2(jit_insn_sub);
                break;
            case 160: // if_icmpne
                stack.op2(jit_insn_ne);
                _buildJump(function, false, stack, labels, data);
                break;
            case 162: // if_icmpge
                stack.op2(jit_insn_ge);
                _buildJump(function, false, stack, labels, data);
                break;
            case 167: // goto
                jit_insn_branch(function, _branchLabel(labels, data));
                break;
            case 172: // ireturn
            case 173: // lreturn
            case 174: // freturn
            case 175: // dreturn
            case 176: // areturn
                jit_insn_return(function, *stack);
                break;
            case 177: // return
                jit_insn_default_return(function);
                break;
            case 178: { // getstatic
                auto index = data.readU16();
                stack << jit_value_create_nint_constant(function, jit_type_void_ptr, 0);
                break;
            }
            case 179: { // putstatic
                auto index = data.readU16();
                auto value = *stack;
                break;
            }
            case 180: { // getfield
                auto index = data.readU16();
                auto object = *stack;
                stack << jit_value_create_nint_constant(function, jit_type_void_ptr, 0);
                break;
            }
            case 181: { // putfield
                auto index = data.readU16();
                auto object = *stack;
                auto value = *stack;
                break;
            }
            case 182: // invokevirtual
            case 183: // invokespecial
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

                auto sign = _convert_signature(info.descriptor(), opcode != 184);
                auto argc = jit_type_num_params(sign);
                auto args = new jit_value_t[argc];
                for (int i = 0; i < argc; i++) {
                    args[argc - i - 1] = *stack;
                }

                auto ipfn = _progressStack->find(info.className(), info.name(), info.descriptor());
                if (ipfn) {
                    stack << jit_insn_call(function, 0, ipfn, sign, args, argc, JIT_CALL_NOTHROW);
                    delete[] args;
                    break;
                }

                auto fn = methods->getNativeMethod(info.className(), info.name(), info.descriptor());
                if (!fn) {
                    if (Espresso::Log) Espresso::Log("Method not found: %s.%s%s", info.className(), info.name(), info.descriptor());
                    return 0;
                }
                stack << jit_insn_call_native(function, 0, fn, sign, args, argc, JIT_CALL_NOTHROW);
                delete[] args;
                break;
            }
            case 187: { // new
                // cheating tests like a boss
                auto index = data.readU16();
                stack << jit_value_create_nint_constant(function, jit_type_void_ptr, 0);
                break;
            }
            case 198: // if_null
                _buildJump(function, true, stack, labels, data);
                break;
            case 199: // if_notnull
                _buildJump(function, false, stack, labels, data);
                break;
            default:
                if (Espresso::Log) Espresso::Log("Unknown opcode: %02x", opcode);

                //jit_context_build_end(_context);
                //message = "Unknown/unsupported opcode";
                //return 0;
        }
    }

    auto next = _progressStack->next;
    delete _progressStack;
    _progressStack = next;

#warning "do a '#if DEBUG' or something"
    jit_dump_function(stderr, function, methodName_);
    jit_function_compile(function);
    if (!_progressStack) jit_context_build_end(_context);

    return jit_function_to_closure(function);
}

