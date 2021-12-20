#include "../include/gallium/gallium.h"
#include <iostream>

void print_string(gallium::String s) {
    std::cout<<s<<std::endl;
}

int main() {
    gallium::String s = "Hello World!";

    s = "bye world!";
    std::cout<<s + " wait, i have something to tell"<<std::endl;
    std::cout<<s<<std::endl;

    s += " bye :^(";
    print_string(s);

    std::cout<<s.pop()<<std::endl;
    print_string(s);

    printf("Buffer: %s\n", (const char*)s);
}