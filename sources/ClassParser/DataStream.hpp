#ifndef ESPRESSO_CLASSPARSER_DATASTREAM_H
#define ESPRESSO_CLASSPARSER_DATASTREAM_H

#include <cstdint>

namespace Espresso {
    namespace ClassParser {
        class DataStream {
        public:
            DataStream() : buffer(0), remaining(0) {
            }
            DataStream(const char * data, int len) {
                buffer = data;
                remaining = len;
            }

            bool reachedEOS() {
                return remaining == 0;
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

            DataStream readBytes(int len) {
                if (remaining < len) return DataStream();
                const char * ptr = buffer;
                buffer += len;
                return DataStream(ptr, len);
            }
        private:
            const char * buffer;
            int remaining;
        };
    };
};

#endif

