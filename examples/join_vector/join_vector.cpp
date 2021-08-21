#include <trivial/strings.h>

#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<int> vec1{1, 2, 3, 4, 5};
    std::vector<char> vec2{'a', 'b', 'c'};
    std::vector<std::string> vec3{"aa", "bb", "cc"};

    // 1---2---3---4---5
    std::cout << trivial::join_vector(vec1, "---") << std::endl;
    // a b c
    std::cout << trivial::join_vector(vec2, " ") << std::endl;
    // aa|bb|cc
    std::cout << trivial::join_vector(vec3, "|") << std::endl;

    return 0;
}