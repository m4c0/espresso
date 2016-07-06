#ifndef ESPRESSO_CLASSPARSER_JIT_H
#define ESPRESSO_CLASSPARSER_JIT_H

#include "ConstantPool/Manager.hpp"
#include "DataStream.hpp"
#include "Failable.hpp"
#include "MethodProvider.hpp"

namespace Espresso {
    namespace ClassParser {
        class JIT : public Failable {
        public:
            JIT();

            JIT & className(const char * sign); 
            JIT & constantPool(ConstantPool::Manager * cpool);
            JIT & dataStream(DataStream data);
            JIT & instanceMethod(bool im);
            JIT & maxLocals(int size);
            JIT & methodName(const char * sign); 
            JIT & signature(const char * sign); 
            JIT & stackSize(int size);

            void * buildFunction() const;
            void * buildFunction(MethodProvider * methods) const;
        private:
            const char * className_;
            ConstantPool::Manager * cpool_;
            DataStream data_;
            const char * methodName_;
            bool instance_;
            const char * signature_;
            int stackSize_;
            int maxLocals_;
        };
    };
};

#endif

