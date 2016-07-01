#ifndef __ESPRESSO_CLASS_H__
#define __ESPRESSO_CLASS_H__

#include "Attributed.hpp"
#include "DataStream.hpp"
#include "Failable.hpp"
#include "Method.hpp"

namespace Espresso {
    namespace ClassParser {
        class Class : public Attributed {
        public:
            Class(const char * filename);
            Class(const char * data, int len);

            const char * name() const {
                return name_;
            }
            const Method * methods() const {
                return methods_;
            }
        private:
            void loadClass(const char * data, int len);

            DataStream data_;
            const char * name_;
            Method * methods_;
        };
    };
};

#endif

