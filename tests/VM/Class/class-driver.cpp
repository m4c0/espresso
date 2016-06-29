#include <iostream>

int main(int argc, char ** argv) {
    if (argc != 2) {
        std::cerr << "Driver must be called with the .class file to test" << std::endl;
        return 1;
    }

    //auto cls = Espresso::VM::Class::ParsedClass(argv[1]);

    return 0;
}

