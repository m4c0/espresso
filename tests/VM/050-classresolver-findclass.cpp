#include "Class/DlOpen.hpp"
#include "Class/Parsed.hpp"
#include "ClassResolver.hpp"

int main() {
    auto cr = Espresso::VM::ClassResolver();
    auto c1 = new Espresso::VM::Class::DlOpen("java/lang/Object");
    cr.addClass(c1);
    if (cr.findClass("java/lang/Object") != c1) return 1;

    auto c2 = new Espresso::VM::Class::DlOpen("java/lang/System");
    cr.addClass(c2);
    if (cr.findClass("java/lang/Object") != c1) return 2;
    if (cr.findClass("java/lang/System") != c2) return 3;
}

