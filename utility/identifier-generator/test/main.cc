#include <iostream>

#include "kplidgen.h"

using namespace kplutl;

int main() {
    Guid guid;
    guid.Generate();
    std::cout << guid << std::endl;

}