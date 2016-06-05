#ifndef ESPRESSO_CLASSPARSER_FAILABLE_H
#define ESPRESSO_CLASSPARSER_FAILABLE_H

namespace Espresso {
    class Failable {
    public:
        operator bool() const {
            return message == 0;
        }
        bool operator !() const {
            return message != 0;
        }
        const char * error() const {
            return message;
        }
    protected:
        const char * message;
    };
};

#endif

