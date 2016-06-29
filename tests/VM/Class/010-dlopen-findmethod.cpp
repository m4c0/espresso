#include "Class/DlOpen.hpp"

#include <iostream>

// Currently, let's use DlOpen with GNU's mangling. Maybe it'll be good
// to do MSVC mangling on Windows. Also, it's easier to just drop
// the ugly mangled names here, instead of defining C++ classes and
// potentially dealing with other issues.
extern "C" void ZN4Test5helloEv() {}
extern "C" void ZN4Test5helloEi() {}
extern "C" void ZN4More4Test6yoohooEv() {}
extern "C" void ZN9More$Test6yoohooEv() {}
extern "C" void ZN3And9More$Test4yeahEv() {}
extern "C" void ZN4Test4pintEi() {}
// Milestone 1
extern "C" void ZN4java4lang6System4exitEi() {}

bool check(const char * clsname, const char * method, const char * signature, void * expected) {
    auto cls = Espresso::VM::Class::DlOpen(clsname);
    auto fn = cls.findMethod(method, signature);
    if (fn != expected) {
        std::cerr << "findMethod returned " << fn << " for " << clsname << "." << method << signature << std::endl;
        return false;
    }
    return true;
}

int main() {
    // Basic example, class without package
    if (!check("Test", "hello", "()V", (void *)ZN4Test5helloEv)) return 1;
    // Same, with a different return (which should be ignored)
    if (!check("Test", "hello", "()I", (void *)ZN4Test5helloEv)) return 2;
    // Same, with a single integer parameter
    if (!check("Test", "hello", "(I)V", (void *)ZN4Test5helloEi)) return 3;
    // Class inside a package
    if (!check("More/Test", "yoohoo", "()V", (void *)ZN4More4Test6yoohooEv)) return 4;
    // Inner class of class without package
    if (!check("More$Test", "yoohoo", "()V", (void *)ZN9More$Test6yoohooEv)) return 5;
    // Inner class of class inside a package
    if (!check("And/More$Test", "yeah", "()V", (void *)ZN3And9More$Test4yeahEv)) return 6;
    // Concrete example for Milestone 1
    if (!check("java/lang/System", "exit", "(I)V", (void *)ZN4java4lang6System4exitEi)) return 7;
    return 0;
}

