#ifndef ESPRESSO_CLASSPARSER_JIT_H
#define ESPRESSO_CLASSPARSER_JIT_H

#include "DataStream.hpp"
#include "Failable.hpp"

namespace Espresso {
    namespace ClassParser {
        class JIT : public Failable {
        public:
            JIT();

            JIT & dataStream(DataStream data);
            JIT & stackSize(int size);

            void * buildFunction();
        private:
            DataStream data_;
            int stackSize_;
        };
    };
};

#endif

