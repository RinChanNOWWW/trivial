#include <algorithm>

#include "trivial/strings.h"

namespace trivial {

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
