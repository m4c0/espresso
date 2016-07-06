#include "DlOpen.hpp"

#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

using namespace Espresso::VM::Class;

char * _mangleCat(char * a, const char * b) {
    int len = strlen(b);
    int adv = sprintf(a, "%d%s", len, b);
    return a + adv;
}

char * _mangle(const char * cls, const char * method, const char * signature) {
    // TODO: this is a major leak
    auto res = new char[10240]; // TODO: range checks
    strcpy(res, "ZN");

    auto ptr = res + 2;

    auto ccls = strdup(cls);
    for (char * tok = strtok(ccls, "/"); tok; tok = strtok(0, "/")) {
        ptr = _mangleCat(ptr, tok);
    }
    delete ccls;

    if (strcmp("<init>", method) == 0) {
        *ptr++ = 'C';
        *ptr++ = '1';
    } else {
        ptr = _mangleCat(ptr, method);
    }

    *ptr++ = 'E';

    if (*signature++ != '(') {
        delete res;
        return 0;
    }
    for (char c = *signature; (c != 0) && (c != ')'); c = *++signature) {
        switch (c) {
            case 'I': *ptr++ = 'i'; break;
            default:
                delete res;
                return 0;
        }
    }
    if (*signature == 0) {
        delete res;
        return 0;
    }
    if (signature[-1] == '(') {
        *ptr++ = 'v';
    }
    *ptr = 0;

    return res;
}

DlOpen::DlOpen(const char * name) : Base(), name_(name) {
}

void * DlOpen::findMethod(const char * method, const char * signature) {
    char * mangled = _mangle(name(), method, signature);
    if (!mangled) return 0; // TODO: test invalid parameters

    void * exe = dlopen(0, 0);
    void * fn = dlsym(exe, mangled);
    dlclose(exe);

    delete mangled;
    return fn;
}

