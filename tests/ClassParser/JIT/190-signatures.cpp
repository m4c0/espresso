#include <iostream>
#include <jit/jit.h>

jit_type_t _convert_signature(const char * sign, bool instance);

static bool _check(const char * jsig, bool instance, jit_type_t ret, int argc, ...) {
    auto sign = _convert_signature(jsig, instance);
    if (sign == 0) {
        std::cerr << jsig << " didn't generate output" << std::endl;
        return false;
    }
    if (jit_type_get_return(sign) != ret) {
        std::cerr << jsig << " gave a different return" << std::endl;
        return false;
    }
    if (jit_type_num_params(sign) != argc) {
        std::cerr << jsig << " gave a different number of arguments" << std::endl;
        return false;
    }
    va_list va;
    va_start(va, argc);
    for (int i = 0; i < argc; i++) {
        if (jit_type_get_param(sign, i) != va_arg(va, jit_type_t)) {
            std::cerr << jsig << " gave a different number of arguments" << std::endl;
            return false;
        }
    }
    va_end(va);

    return true;
}

bool _fails(const char * jsig) {
    auto sign = _convert_signature(jsig, false);
    if (sign != 0) {
        std::cerr << "'" << jsig << "' did generate output" << std::endl;
        return false;
    }
    sign = _convert_signature(jsig, true);
    if (sign != 0) {
        std::cerr << "'" << jsig << "' did generate output for instance method" << std::endl;
        return false;
    }
    return true;
}

int main() {
    if (!_fails("")) return 1;
    if (!_fails("(")) return 1;
    if (!_fails("()")) return 1;
    if (!_fails("V")) return 1;
    if (!_fails("()VV")) return 1;
    if (!_fails("()L")) return 1;
    if (!_fails("(L)V")) return 1;
    if (!_fails("(L;)V")) return 1;
    if (!_fails("(;)V")) return 1;
    if (!_fails("(OK;)V")) return 1;

    if (!_check("()V", false, jit_type_void, 0)) return 1;
    if (!_check("()I", false, jit_type_int, 0)) return 1;
    if (!_check("()Z", false, jit_type_int, 0)) return 1;
    if (!_check("()J", false, jit_type_long, 0)) return 1;
    if (!_check("()D", false, jit_type_float64, 0)) return 1;
    if (!_check("()F", false, jit_type_float32, 0)) return 1;
    if (!_check("()LT;", false, jit_type_void_ptr, 0)) return 1;
    if (!_check("()LT/T;", false, jit_type_void_ptr, 0)) return 1;
    if (!_check("()LT/T$T;", false, jit_type_void_ptr, 0)) return 1;
    if (!_check("(I)I", false, jit_type_int, 1, jit_type_int)) return 1;
    if (!_check("(JZ)I", false, jit_type_int, 2, jit_type_long, jit_type_int)) return 1;
    if (!_check("(DF)D", false, jit_type_float64, 2, jit_type_float64, jit_type_float32)) return 1;
    if (!_check("(LT;LMeh;)I", false, jit_type_int, 2, jit_type_void_ptr, jit_type_void_ptr)) return 1;

    if (!_check("()V", true, jit_type_void, 1, jit_type_void_ptr)) return 1;
    if (!_check("(I)I", true, jit_type_int, 2, jit_type_void_ptr, jit_type_int)) return 1;

    return 0;
}

