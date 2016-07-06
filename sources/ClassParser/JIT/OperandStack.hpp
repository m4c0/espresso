#ifndef ESPRESSO_CLASSPARSER_JIT_OPERANDSTACK_H
#define ESPRESSO_CLASSPARSER_JIT_OPERANDSTACK_H

#include <jit/jit.h>

namespace Espresso {
    namespace ClassParser {
        namespace JITInternals {
            class OperandStack {
            public:
                OperandStack(jit_function_t fn, int max) : function_(fn) {
                    // TODO: check for overruns and underruns
                    current = stack = new jit_value_t[max];
                }

                OperandStack & operator<<(jit_value_t v) {
                    *current = v;
                    current++;
                    return *this;
                }
                jit_value_t operator*() {
                    current--;
                    return *current;
                }

                void op2(jit_value_t (*fn)(jit_function_t, jit_value_t, jit_value_t)) {
                    auto one = **this;
                    auto two = **this;
                    *this << fn(function_, two, one);
                }
            private:
                jit_value_t * stack;
                jit_value_t * current;
                jit_function_t function_;
            };
        };
    };
};

#endif

