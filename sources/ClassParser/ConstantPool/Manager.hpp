#ifndef ESPRESSO_CLASSPARSER_CONSTANTPOOL_MANAGER_H
#define ESPRESSO_CLASSPARSER_CONSTANTPOOL_MANAGER_H

#include "DataStream.hpp"
#include "Item.hpp"

namespace Espresso {
    namespace ClassParser {
        namespace ConstantPool {
            class Manager : public Failable {
            public:
                Manager(DataStream & data);
                ~Manager();

                template<class T>
                const T & itemForIndex(int idx) const {
                    return *(T *)items[idx - 1];
                }

                const Item * const * operator[](int idx) const;

                bool itemMatchesTag(int idx, int type) const;
            private:
                Item ** items;
                int size;
            };
        };
    };
};

#endif

