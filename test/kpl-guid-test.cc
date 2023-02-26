#include <iostream>

#include "kpl-guid.h"

using namespace kplge;

int main(){
    Guid guid = generate_guid();

    std::cout << guid <<std::endl;
}