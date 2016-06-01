#ifndef ESPRESSO_CLASSPARSER_ATTRIBUTE_H
#define ESPRESSO_CLASSPARSER_ATTRIBUTE_H

#include "ConstantPool/Manager.hpp"
#include "DataStream.hpp"
#include "Failable.hpp"

namespace Espresso {
    namespace ClassParser {
        class Attribute : public Failable {
        public:
            Attribute(ConstantPool::Manager & cpool, DataStream & data);

            const char * name() const {
                return name_;
            }
            DataStream data() const {
                return data_;
            }

        private:
            const char * name_;
            DataStream data_;
        };
    };
};

#endif

