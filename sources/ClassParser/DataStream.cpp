#include "DataStream.hpp"

#include <cstdint>
#include <stdio.h>
#include <string.h>

using namespace Espresso::ClassParser;

DataStream::DataStream() : buffer(0), remaining(0), original(0) {
}
DataStream::DataStream(const char * data, int len) : original(0) {
    buffer = data;
    remaining = len;
}
DataStream::DataStream(const char * data, int len, bool copy) {
    if (!copy) {
        buffer = data;
        remaining = len;
        original = 0;
        return;
    }

    char * ptr = new char[len];
    memcpy(ptr, data, len);

    buffer = original = ptr;
    remaining = len;
}
DataStream::~DataStream() {
    if (original) delete original;
}

bool DataStream::reachedEOS() {
    return remaining == 0;
}

uint8_t DataStream::readU8() {
    if (remaining < 1) return 0;
    auto result = *buffer;
    buffer++;
    remaining--;
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

