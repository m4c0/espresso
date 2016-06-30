#ifndef ESPRESSO_CLASSPARSER_METHOD_H
#define ESPRESSO_CLASSPARSER_METHOD_H

#include "Attribute/Code.hpp"
#include "ClassEntry.hpp"
#include "ConstantPool/Manager.hpp"

namespace Espresso {
    namespace ClassParser {
        class Method : public ClassEntry {
        public:
            Method();
            Method(ConstantPool::Manager & cpool, DataStream & data);

            void * code() const { return code_.code(); }

        private:
            Attribute::Code code_;
        };
    };
};

#endif

