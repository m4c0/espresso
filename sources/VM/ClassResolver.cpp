#include "ClassResolver.hpp"

#include <string.h>

using namespace Espresso::VM;

class ClassResolver::Node {
public:
    Node(Class::Base * cls, Node * next) : data_(cls), next_(next) {
    }

    Class::Base * data_;
    Node * next_;
};

ClassResolver::ClassResolver() : first_(0) {
}

void ClassResolver::addClass(Class::Base * cls) {
    cls->classResolver(this);

    first_ = new Node(cls, first_);
}

Class::Base * ClassResolver::findClass(const char * name) {
    Node * n = first_;
    while (n) {
        if (strcmp(n->data_->name(), name) == 0) {
            return n->data_;
        }
        n = n->next_;
    }
    return 0;
}

