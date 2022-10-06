#include "../include/gallium/gallium.h"
#include <iostream>

int main() {
    int ara[] = {1, 2, 3, 4};
    gallium::Vec<int> v = gallium::Vec<int>(ara, 4);
    v.push(9);

    std::cout<<v[0]<<" "<<v[3]<<std::endl;
    std::cout<<v<<std::endl;

    gallium::Vec<std::string> strs;
    strs.push("Hello world");

    std::cout<<strs[0]<<std::endl;
}