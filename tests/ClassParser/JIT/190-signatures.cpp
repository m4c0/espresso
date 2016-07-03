#include <iostream>
#include <jit/jit.h>

jit_type_t _convert_signature(const char * sign);

static bool _check(const char * jsig, jit_type_t ret, int argc, ...) {
    auto sign = _convert_signature(jsig);
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
    auto sign = _convert_signature(jsig);
    if (sign != 0) {
        std::cerr << "'" << jsig << "' did generate output" << std::endl;
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

    if (!_check("()V", jit_type_void, 0)) return 1;
    if (!_check("()I", jit_type_int, 0)) return 1;
    if (!_check("()J", jit_type_long, 0)) return 1;
    if (!_check("(I)I", jit_type_int, 1, jit_type_int)) return 1;
    if (!_check("(JI)I", jit_type_int, 2, jit_type_long, jit_type_int)) return 1;
    return 0;
}

