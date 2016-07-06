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
            ClassEntry();
            ClassEntry(ConstantPool::Manager & cpool, DataStream & data);

            bool isAbstract() const;
            bool isStatic() const;

            const char * descriptor() const {
                return descriptor_;
            }
            const char * name() const {
                return name_;
            }
        private:
            const char * name_;
            const char * descriptor_;
            int access_;
        };
    };
};

#endif

