#ifndef ESPRESSO_CLASSPARSER_ATTRIBUTED_H
#define ESPRESSO_CLASSPARSER_ATTRIBUTED_H

#include "Attribute/Base.hpp"
#include "DataStream.hpp"
#include "Failable.hpp"
#include "ConstantPool/Manager.hpp"

namespace Espresso {
    namespace ClassParser {
        class Attributed : public Failable {
        public:
            virtual ~Attributed();

            template<class T>
            const T & itemForName(const char * name) {
                return *(T *)baseItemForName(name);
            }

        protected:
            bool parseAttributes(ConstantPool::Manager & cpool, DataStream & data);
        private:
            Attribute::Base * baseItemForName(const char * name);

            Attribute::Base ** attributes;
        };
    };
};

#endif

