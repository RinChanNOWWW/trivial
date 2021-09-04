#include <trivial/strings.h>

#include <iostream>
#include <string>
#include <vector>

void print_vec(const std::vector<std::string> &vec) {
    for (const auto &s : vec) {
        std::cout << s << " ";
    }
    std::cout << std::endl;
}

int main() {
    print_vec(trivial::split("123.321.asdsad", "."));
    print_vec(trivial::split(std::string("aaa<=>bbb<=>ccc"), "<=>"));
    return 0;
}