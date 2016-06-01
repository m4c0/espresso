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

            const char *    name()  const { return name_; }
            const uint8_t * bytes() const { return bytes_; }

        private:
            const char * name_;
            const uint8_t * bytes_;
        };
    };
};

#endif

