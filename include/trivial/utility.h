#ifndef UTILITY_H_
#define UTILITY_H_

#include <iostream>
#include <string>
#include <vector>

namespace trivial {

/**
 * @brief Get std::vector<int> from string like "[1,2,3,4,5]"
 *
 * @param str
 * @return std::vector<int>
 */
std::vector<int> GetIntVecFromStr(const std::string str);

/**
 * @brief Get std::vector<std::vector<int>> from string like
 * "[[1,2],[1,2,3],[3,2]]"
 *
 * @return std::vector<std::vector<int>>
 */
std::vector<std::vector<int>> Get2DimIntVecFromStr(const std::string str);

/**
 * @brief Print a std::vector
 *
 * @tparam T printable(through cout) type
 * @tparam S printable(through cout) type
 * @param vec the vector to print
 * @param sep the seperator
 */
template <typename T, typename S>
inline void PrintVec(const std::vector<T> &vec, S sep) {
    if (vec.size() > 0) {
        std::cout << vec.front();
        for (auto iter = vec.begin() + 1; iter < vec.end(); iter++) {
            std::cout << sep << *iter;
        }
    }
}

}  // namespace trivial

#endif