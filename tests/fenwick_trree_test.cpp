#include "gtest/gtest.h"
#include "trivial/fenwick_tree.h"

namespace trivial {

TEST(FenwickTreeTest, SimpleTest) {
    FenwickTree<int> tree{1, 7, 3, 0, 5, 8, 3, 2, 6, 2, 1, 1, 4, 5};
    // test prefix sum
    const auto v = tree.GetOriginalNums();
    std::vector<int> presum(v.size());
    presum[0] = v[0];
    for (int i = 1; i < tree.Size(); i++) {
        presum[i] = presum[i - 1] + v[i];
    }
    for (int i = 0; i < tree.Size(); i++) {
        ASSERT_EQ(presum[i], tree.PrefixSum(i));
    }

    // test update
    std::vector<int> to_update = {1, 2, 3, -3, -2, -1, 5,
                                  6, 7, 8, 9,  10, 11, -12};
    for (int i = 0; i < to_update.size(); i++) {
        tree.Update(i, to_update[i]);
    }
    ASSERT_EQ(to_update, tree.GetOriginalNums());
    presum[0] = to_update[0];
    for (int i = 1; i < tree.Size(); i++) {
        presum[i] = presum[i - 1] + to_update[i];
    }
    for (int i = 0; i < tree.Size(); i++) {
        ASSERT_EQ(presum[i], tree.PrefixSum(i));
    }
}

}  // namespace trivial