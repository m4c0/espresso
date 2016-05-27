#ifndef __ESPRESSO_CLASS_H__
#define __ESPRESSO_CLASS_H__

namespace Espresso {
    class Class {
    public:
        Class(const char * data, int len);
        ~Class();

        operator bool() {
            return message != 0;
        }
        bool operator !() {
            return message == 0;
        }
        const char * error() {
            return message;
        }
    private:
        const char * message;
    };
};

#endif

