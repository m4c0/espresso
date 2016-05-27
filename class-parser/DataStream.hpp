#ifndef ESPRESSO_CLASSPARSER_DATASTREAM_H
#define ESPRESSO_CLASSPARSER_DATASTREAM_H

#include <cstdint>

namespace Espresso {
    class DataStream {
    public:
        DataStream(const char * data, int len) {
            buffer = data;
            remaining = len;
        }

        uint8_t readU8() {
            if (remaining < 1) return 0;
            auto result = *buffer;
            buffer++;
            remaining--;
            return result;
        }
        uint16_t readU16() {
            if (remaining < 2) return 0;
            return (readU8() << 8) | readU8();
        }

        uint32_t readU32() {
            if (remaining < 4) return 0;
            return (readU16() << 16) | readU16();
        }
    private:
        const char * buffer;
        int remaining;
    };
};

#endif

