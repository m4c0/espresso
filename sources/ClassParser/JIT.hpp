#ifndef ESPRESSO_CLASSPARSER_JIT_H
#define ESPRESSO_CLASSPARSER_JIT_H

#include "DataStream.hpp"
#include "Failable.hpp"

namespace Espresso {
    namespace ClassParser {
        class JIT : public Failable {
        public:
            JIT(DataStream data);
            JIT(DataStream data, int stackSize);

            void * function() {
                return function_;
            }
        private:
            void * function_;
        };
    };
};

#endif

