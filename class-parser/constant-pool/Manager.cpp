#include "Manager.hpp"

#include "ClassInfo.hpp"
#include "Double.hpp"
#include "FieldRefInfo.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "InterfaceMethodRefInfo.hpp"
#include "Logger.hpp"
#include "Long.hpp"
#include "MethodRefInfo.hpp"
#include "NameAndType.hpp"
#include "StringInfo.hpp"
#include "Utf8.hpp"

using namespace Espresso::ClassParser::ConstantPool;

Manager::Manager(DataStream & data) {
    auto cpoolMax = data.readU16();
    if (cpoolMax == 0) {
        message = "Invalid constant pool";
        return;
    }
    size = cpoolMax - 1;

    items = new Item *[size];
    for (int idx = 0; idx < size; idx++) {
        items[idx] = 0;
    }
    for (int idx = 0; idx < size; idx++) {
        bool itemTakesExtraId = false;
        auto type = data.readU8();
        switch (type) {
            case 1:
                items[idx] = new Utf8(data);
                break;
            case 3:
                items[idx] = new Integer(data);
                break;
            case 4:
                items[idx] = new Float(data);
                break;
            case 5:
                items[idx] = new Long(data);
                itemTakesExtraId = true;
                break;
            case 6:
                items[idx] = new Double(data);
                itemTakesExtraId = true;
                break;
            case 7:
                items[idx] = new ClassInfo(*this, data);
                break;
            case 8:
                items[idx] = new StringInfo(*this, data);
                break;
            case 9:
                items[idx] = new FieldRefInfo(*this, data);
                break;
            case 10:
                items[idx] = new MethodRefInfo(*this, data);
                break;
            case 11:
                items[idx] = new InterfaceMethodRefInfo(*this, data);
                break;
            case 12:
                items[idx] = new NameAndType(*this, data);
                break;
            default: 
                if (Espresso::Log) Espresso::Log("Found unknown constant pool item tag: %d", type);
                message = "Invalid constant pool item type";
                return;
        }
        if (!*items[idx]) {
            message = items[idx]->error();
            return;
        }
        if (itemTakesExtraId) {
            idx++; // 64-bit data does that to constant pool, due to reasons
        }
    }

    message = 0;
}
Manager::~Manager() {
    if (!items) return;

    for (int i = 0; i < size; i++) {
        if (items[i] != 0) delete items[i];
    }
    delete[] items;
}

const Item * const * Manager::operator[](int idx) const {
    if (idx < 1) return 0;
    if (idx > size) return 0;
    return items + idx - 1;
}

