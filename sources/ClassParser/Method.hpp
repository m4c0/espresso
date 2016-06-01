#ifndef ESPRESSO_CLASSPARSER_METHOD_H
#define ESPRESSO_CLASSPARSER_METHOD_H

#include "ClassEntry.hpp"

namespace Espresso {
    class Method : public ClassEntry {
    public:
        Method(DataStream & data);
    };
};

#endif

