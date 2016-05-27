#ifndef __ESPRESSO_CLASS_H__
#define __ESPRESSO_CLASS_H__

#include <cstdint>

namespace Espresso {
    namespace ClassInternals {
        class ConstantPoolInfo {
        };
        class FieldInfo {
        };
        class MethodInfo {
        };
        class AttributeInfo {
        };
    };

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
        typedef ClassInternals::ConstantPoolInfo cp_info;
        typedef ClassInternals::FieldInfo field_info;
        typedef ClassInternals::MethodInfo method_info;
        typedef ClassInternals::AttributeInfo attribute_info;

        uint32_t         magic;
        uint16_t         minorVersion;
        uint16_t         majorVersion;
        uint16_t         constantPoolCount;
        cp_info        * constantPool;
        uint16_t         accessFlags;
        uint16_t         thisClass;
        uint16_t         superClass;
        uint16_t         interfacesCount;
        uint16_t       * interfaces;
        uint16_t         fieldsCount;
        field_info     * fields;
        uint16_t         methodsCount;
        method_info    * methods;
        uint16_t         attributesCount;
        attribute_info * attributes;

        const char * message;
    };
};

#endif

