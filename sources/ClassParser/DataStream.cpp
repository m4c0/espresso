#include "DataStream.hpp"

#include <cstdint>
#include <stdio.h>
#include <string.h>

using namespace Espresso::ClassParser;

DataStream::DataStream() : buffer(0), remaining(0), original(0), read(0) {
}
DataStream::DataStream(const DataStream & copy) : original(0), read(0) {
    *this = copy;
}
DataStream::DataStream(const char * data, int len) : original(0), read(0) {
    buffer = data;
    remaining = len;
}
DataStream::DataStream(const char * data, int len, bool copy) : original(0), read(0) {
    if (!copy) {
        buffer = data;
        remaining = len;
        original = 0;
        return;
    }

    *this = DataStream(data, len);
}
DataStream::~DataStream() {
    if (original) delete original;
}

DataStream & DataStream::operator=(const DataStream & copy) {
    if (original) delete original;

    const char * data = copy.buffer;
    int len = copy.remaining;

    char * ptr = new char[len];
    memcpy(ptr, data, len);

    buffer = original = ptr;
    remaining = len;

    return *this;
}

bool DataStream::reachedEOS() {
    return remaining == 0;
}

uint8_t DataStream::readU8() {
    if (remaining < 1) return 0;
    auto result = *buffer;
    buffer++;
    remaining--;
    read++;
    return result;
}

uint16_t DataStream::readU16() {
    if (remaining < 2) return 0;
    return (readU8() << 8) | readU8();
}

uint32_t DataStream::readU32() {
    if (remaining < 4) return 0;
    return (readU16() << 16) | readU16();
}

DataStream DataStream::readBytes(int len) {
    if (remaining < len) return DataStream();
    const char * ptr = buffer;
    buffer += len;
    return DataStream(ptr, len);
}

