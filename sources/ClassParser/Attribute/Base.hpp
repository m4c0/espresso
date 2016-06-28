#ifndef ESPRESSO_CLASSPARSER_ATTRIBUTE_BASE_H
#define ESPRESSO_CLASSPARSER_ATTRIBUTE_BASE_H

namespace Espresso {
    namespace ClassParser {
        namespace Attribute {
            class Base {
            public:
                Base();
                Base(const char * name);

                const char * name() { return name_; }
            private:
                const char * name_;
            };
        };
    };
};

#endif

