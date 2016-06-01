#ifndef ESPRESSO_CLASSPARSER_LOGGER_H
#define ESPRESSO_CLASSPARSER_LOGGER_H

// TODO: eventually create a proper lib with "common" stuff or evolve this log concept

namespace Espresso {
    extern void (*Log)(const char * fmt, ...);
};

#endif

