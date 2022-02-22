#include "trivial/algorithm.h"

#include "gtest/gtest.h"

namespace trivial {

TEST(AlgoTest, QuickPower) {
    auto pow = QuickPow<int, int>(3, 9, 1);
    ASSERT_EQ(pow, 19683);
}

TEST(AlgoTest, HeapSort) {
    std::vector<int> vec{5, 2, 5, 6, 1, 7, 3, 73, 2, 82, 2, 3};
    HeapSort(vec, [](int a, int b) { return a < b; });
    auto sorted = [](const std::vector<int> &v) {
        for (int i = 1; i < v.size(); i++) {
            if (v[i] < v[i - 1]) {
                return false;
            }
        }
        return true;
    };
    ASSERT_TRUE(sorted(vec));
}

}  // namespace trivial
