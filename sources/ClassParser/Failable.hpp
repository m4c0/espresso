#ifndef ESPRESSO_CLASSPARSER_FAILABLE_H
#define ESPRESSO_CLASSPARSER_FAILABLE_H

namespace Espresso {
    class Failable {
    public:
        operator bool() {
            return message == 0;
        }
        bool operator !() {
            return message != 0;
        }
        const char * error() {
            return message;
        }
    protected:
        const char * message;
    };
};

#endif

