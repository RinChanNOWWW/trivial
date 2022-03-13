#include "trivial/strings.h"

#include <algorithm>
#include <numeric>

#include "macro.h"

namespace trivial {

/**
 * @brief join a std::vector
 * @param vec the std::vector to be joined
 * @param connector the join connector
 * @return the joined string
 */
template <typename T>
std::string JoinVector(const std::vector<T> &vec,
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

#define GENERATE_FOR(T)                                        \
    template std::string JoinVector(const std::vector<T> &vec, \
                                    const std::string &connector);
FOREACH_STRINGIFYABLE_TYPE
#undef GENERATE_FOR

/**
 * @brief join a std::vector
 * @param vec the std::vector to be joined
 * @param connector the join connector
 * @return the joined string
 */
std::string JoinVector(const std::vector<char> &vec,
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
 * @return the joined string
 */
std::string JoinVector(const std::vector<std::string> &vec,
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

/**
 * @brief split a string
 * @param s the original string
 * @param delim the delimiter
 * @return the splited string vector
 */
std::vector<std::string> Split(const std::string s, const std::string delim) {
    std::vector<std::string> res;
    size_t last = 0, next = 0;
    while ((next = s.find(delim, last)) != std::string::npos) {
        res.push_back(s.substr(last, next - last));
        last = next + delim.length();
    }
    res.push_back(s.substr(last));
    return res;
}

/**
 * @brief split a string
 * @param chars the origin char literal
 * @param delim the delimiter
 * @return the splited string vector
 */
std::vector<std::string> Split(const char *chars, const std::string delim) {
    std::string s(chars);
    std::vector<std::string> res;
    size_t last = 0, next = 0;
    while ((next = s.find(delim, last)) != std::string::npos) {
        res.push_back(s.substr(last, next - last));
        last = next + delim.length();
    }
    res.push_back(s.substr(last));
    return res;
}

}  // namespace trivial