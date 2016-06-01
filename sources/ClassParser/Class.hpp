#ifndef __ESPRESSO_CLASS_H__
#define __ESPRESSO_CLASS_H__

#include "Attributed.hpp"
#include "Failable.hpp"

namespace Espresso {
    namespace ClassParser {
        class Class : public Attributed {
        public:
            Class(const char * data, int len);
            ~Class();
        };
    };
};

#endif

