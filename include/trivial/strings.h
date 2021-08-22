#pragma once

#include <numeric>
#include <string>
#include <vector>

namespace trivial {

/**
 * @brief join a std::vector
 * @param vec the std::vector to be joined
 * @param connector the join connector
 */
template <typename T>
std::string join_vector(const std::vector<T> &vec,
                        const std::string &connector) {
    if (vec.size() == 0) {
        return "";
    }
    if (vec.size() == 1) {
        return std::to_string(vec[0]);
    }
    return std::accumulate(
        std::next(vec.begin()), vec.end(), std::to_string(vec[0]),
        [connector](std::string a, T b) {
            return std::move(a) + connector + std::to_string(b);
        });
}

/**
 * @brief join a std::vector
 * @param vec the std::vector to be joined
 * @param connector the join connector
 */
std::string join_vector(const std::vector<char> &vec,
                        const std::string &connector) {
    if (vec.size() == 0) {
        return "";
    }
    if (vec.size() == 1) {
        return std::string(1, vec[0]);
    }
    return std::accumulate(
        std::next(vec.begin()), vec.end(), std::string(1, vec[0]),
        [connector](std::string a, char b) {
            return std::move(a) + connector + std::string(1, b);
        });
}

/**
 * @brief join a std::vector
 * @param vec the std::vector to be joined
 * @param connector the join connector
 */
std::string join_vector(const std::vector<std::string> &vec,
                        const std::string &connector) {
    if (vec.size() == 0) {
        return "";
    }
    if (vec.size() == 1) {
        return vec[0];
    }
    return std::accumulate(std::next(vec.begin()), vec.end(), vec[0],
                           [connector](std::string a, std::string b) {
                               return std::move(a) + connector + b;
                           });
}

}  // namespace trivial