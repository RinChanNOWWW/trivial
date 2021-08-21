#include <trivial/algorithm.h>
#include <trivial/strings.h>

#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec{5, 2, 5, 6, 1, 7, 3, 73, 2, 82, 2, 3};
    // asc
    trivial::heap_sort(vec, [](int a, int b) { return a < b; });
    // 1,2,2,2,3,3,5,5,6,7,73,82
    std::cout << trivial::join_vector(vec, ",") << std::endl;
    // desc
    trivial::heap_sort(vec, [](int a, int b) { return a > b; });
    // 82,73,7,6,5,5,3,3,2,2,2,1
    std::cout << trivial::join_vector(vec, ",") << std::endl;
    return 0;
}