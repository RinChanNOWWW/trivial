#ifndef STRINGS_H_
#define STRINGS_H_

#include <algorithm>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

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

/**
 * @brief trim from begin of a string
 * @param str the origin string
 * @param ws the chars to trim
 * @return the trimmed string
 */
template <typename Chars>
inline std::string &LTrim(std::string &s, Chars ws) {
    s.erase(0, s.find_first_not_of(ws));
    return s;
}

/**
 * @brief trim from end of a string
 * @param str the origin string
 * @param ws the chars to trim
 */
template <typename Chars>
inline std::string &RTrim(std::string &s, Chars ws) {
    s.erase(s.find_last_not_of(ws) + 1);
    return s;
}

/**
 * @brief trim a string from both sides
 * @param str the origin string
 * @param ws the chars to trim
 */
template <typename Chars>
inline std::string &Trim(std::string &s, Chars ws) {
    LTrim(RTrim(s, ws), ws);
    return s;
}

/**
 * @brief Get std::vector<int> from string like "[1,2,3,4,5]"
 *
 * @param str
 * @return std::vector<int>
 */
std::vector<int> GetIntVecFromStr(const std::string str) {
    std::string s = str;
    std::vector<std::string> raw = Split(LTrim(RTrim(s, "]"), "["), ",");
    std::vector<int> ret;
    std::transform(raw.begin(), raw.end(), std::back_inserter(ret),
                   [](const std::string e) { return stoi(e); });
    return ret;
}

/**
 * @brief Get std::vector<std::vector<int>> from string like
 * "[[1,2],[1,2,3],[3,2]]"
 *
 * @return std::vector<std::vector<int>>
 */
std::vector<std::vector<int>> Get2DimIntVecFromStr(const std::string str) {
    std::string s = str;
    std::vector<std::vector<int>> ret;
    std::vector<std::string> raw = Split(LTrim(RTrim(s, "]"), "["), "],[");
    for (const std::string &e : raw) {
        ret.push_back(GetIntVecFromStr(e));
    }
    return ret;
}

}  // namespace trivial

#endif