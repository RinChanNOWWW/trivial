#include "trivial/utility.h"

#include "gtest/gtest.h"

namespace trivial

{
TEST(UtilityTest, GetVec) {
    std::string input = "[1,2,3,4]";
    std::vector<int> output = {1, 2, 3, 4};
    ASSERT_EQ(GetIntVecFromStr(input), output);
}

TEST(UtilityTest, Get2DimVec) {
    std::string input = "[1,2],[2,3,4],[5,6,7]";
    std::vector<std::vector<int>> output = {{1, 2}, {2, 3, 4}, {5, 6, 7}};
    ASSERT_EQ(Get2DimIntVecFromStr(input), output);
}
}  // namespace trivial