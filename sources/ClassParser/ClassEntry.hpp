#ifndef ESPRESSO_CLASSPARSER_CLASSENTRY_H
#define ESPRESSO_CLASSPARSER_CLASSENTRY_H

#include "Attributed.hpp"
#include "ConstantPool/Manager.hpp"
#include "DataStream.hpp"
#include "Failable.hpp"

namespace Espresso {
    namespace ClassParser {
        class ClassEntry : public Attributed {
        public:
            ClassEntry(ConstantPool::Manager & cpool, DataStream & data);
        };
    };
};

#endif

