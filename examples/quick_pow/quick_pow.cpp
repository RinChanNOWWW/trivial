#include <trivial/algorithm.h>

#include <iostream>

int main() {
    // 19683
    std::cout << trivial::quick_pow<int, int>(3, 9, 1) << std::endl;
    return 0;
}