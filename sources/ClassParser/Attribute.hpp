#ifndef ESPRESSO_CLASSPARSER_ATTRIBUTE_H
#define ESPRESSO_CLASSPARSER_ATTRIBUTE_H

#include "DataStream.hpp"
#include "Failable.hpp"

namespace Espresso {
    class Attribute : public Failable {
    public:
        Attribute(DataStream & data);
    };
};

#endif

