#ifndef STRINGS_H_
#define STRINGS_H_

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
std::string JoinVector(const std::vector<T> &vec, const std::string &connector);

// extern template std::string JoinVector(const std::vector<int> &vec,
//                                        const std::string &connector);

/**
 * @brief join a std::vector
 * @param vec the std::vector to be joined
 * @param connector the join connector
 * @return the joined string
 */
std::string JoinVector(const std::vector<char> &vec,
                       const std::string &connector);

/**
 * @brief join a std::vector
 * @param vec the std::vector to be joined
 * @param connector the join connector
 * @return the joined string
 */
std::string JoinVector(const std::vector<std::string> &vec,
                       const std::string &connector);

/**
 * @brief split a string
 * @param s the original string
 * @param delim the delimiter
 * @return the splited string vector
 */
std::vector<std::string> Split(const std::string s, const std::string delim);
/**
 * @brief split a string
 * @param chars the origin char literal
 * @param delim the delimiter
 * @return the splited string vector
 */
std::vector<std::string> Split(const char *chars, const std::string delim);

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

}  // namespace trivial

#endif