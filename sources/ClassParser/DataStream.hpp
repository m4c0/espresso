#ifndef ESPRESSO_CLASSPARSER_DATASTREAM_H
#define ESPRESSO_CLASSPARSER_DATASTREAM_H

#include <cstdint>

namespace Espresso {
    namespace ClassParser {
        class DataStream {
        public:
            DataStream();
            DataStream(const DataStream & copy);
            DataStream(const char * data, int len);
            DataStream(const char * data, int len, bool copy);
            ~DataStream();

            DataStream & operator=(const DataStream & copy);

            int bytesRead() { return read; }
            int bytesRemaining() { return remaining; }

            bool reachedEOS();

            uint8_t readU8();
            uint16_t readU16();
            uint32_t readU32();

            DataStream readBytes(int len);
        private:
            const char * original;
            const char * buffer;
            int remaining;
            int read;
        };
    };
};

#endif

