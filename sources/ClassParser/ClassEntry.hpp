#ifndef ESPRESSO_CLASSPARSER_CLASSENTRY_H
#define ESPRESSO_CLASSPARSER_CLASSENTRY_H

#include "DataStream.hpp"
#include "Failable.hpp"

namespace Espresso {
    class ClassEntry : public Failable {
    public:
        ClassEntry(DataStream & data);
    };
};

#endif

