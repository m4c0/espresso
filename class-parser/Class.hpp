#ifndef __ESPRESSO_CLASS_H__
#define __ESPRESSO_CLASS_H__

#include "Failable.hpp"

namespace Espresso {
    namespace ClassParser {
        class Class : public ::Espresso::Failable {
        public:
            Class(const char * data, int len);
            ~Class();
        };
    };
};

#endif

