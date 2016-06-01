#ifndef ESPRESSO_CLASSPARSER_ATTRIBUTED_H
#define ESPRESSO_CLASSPARSER_ATTRIBUTED_H

#include "DataStream.hpp"
#include "Failable.hpp"
#include "ConstantPool/Manager.hpp"

namespace Espresso {
    namespace ClassParser {
        class Attributed : public Failable {
        public:
            DataStream code() const {
                return code_;
            }

        protected:
            bool parseAttributes(ConstantPool::Manager & cpool, DataStream & data);

        private:
            DataStream code_;
        };
    };
};

#endif

