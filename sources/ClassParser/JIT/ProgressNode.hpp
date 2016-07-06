#ifndef ESPRESSO_CLASSPARSER_JIT_PROGRESSNODE_H
#define ESPRESSO_CLASSPARSER_JIT_PROGRESSNODE_H

#include <jit/jit.h>
#include <string.h>

namespace Espresso {
    namespace ClassParser {
        namespace JITInternals {
            class ProgressNode {
            public:
                ProgressNode(const char * c, const char * m, const char * s, jit_function_t f, ProgressNode * n) : clazz(c), method(m), signature(s), function(f), next(n) {}

                jit_function_t find(const char * c, const char * m, const char * s) {
                    if ((strcmp(clazz, c) == 0) && (strcmp(method, m) == 0) && (strcmp(signature, s) == 0)) {
                        return function;
                    }
                    if (!next) return 0;
                    return next->find(c, m, s);
                }
            
                const char * clazz;
                const char * method;
                const char * signature;
                jit_function_t function;
            
                ProgressNode * next;
            };
        };
    };
};

#endif

