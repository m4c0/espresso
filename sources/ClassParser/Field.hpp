#ifndef ESPRESSO_CLASSPARSER_FIELD_H
#define ESPRESSO_CLASSPARSER_FIELD_H

#include "ClassEntry.hpp"

namespace Espresso {
    class Field : public ClassEntry {
    public:
        Field(DataStream & data);
    };
};

#endif

