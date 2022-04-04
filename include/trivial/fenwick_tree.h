#ifndef FENWICK_TREE_H_
#define FENWICK_TREE_H_

#include <type_traits>
#include <vector>

namespace trivial {

/**
 * @brief Fenwick tree, or binary index tree
 *
 */
template <typename T>
class FenwickTree {
   public:
    /**
     * @brief Construct a new Fenwick Tree object from vector.
     *
     * @param nums the original vector
     */
    FenwickTree(
        const std::vector<
            typename std::enable_if<std::is_signed<T>::value, T>::type> &nums)
        : tree_(nums.size() + 1), original_nums_(nums) {
        for (int i = 0; i < nums.size(); i++) {
            Add(i + 1, nums[i]);
        }
    }

    FenwickTree(
        const std::initializer_list<
            typename std::enable_if<std::is_signed<T>::value, T>::type> &nums)
        : tree_(nums.size() + 1), original_nums_(nums) {
        size_t index = 0;
        for (auto n : nums) {
            Add(index + 1, n);
            index += 1;
        }
    }

    /**
     * @brief Return the size of the tree.
     *
     * @return size_t
     */
    inline size_t Size() { return original_nums_.size(); }

    /**
     * @brief Update the val at inddex.
     *
     * @param index
     * @param val
     */
    void Update(size_t index, T val) {
        Add(index + 1, val - original_nums_[index]);
        original_nums_[index] = val;
    }

    /**
     * @brief Get the prefix sum at index.
     *
     * @param index
     * @return T
     */
    T PrefixSum(size_t index) {
        index += 1;
        T sum = 0;
        while (index > 0) {
            sum += tree_[index];
            index -= LowBits(index);
        }
        return sum;
    }

    std::vector<T> GetOriginalNums() { return original_nums_; }

   private:
    inline T LowBits(T x) { return x & (-x); }
    inline void Add(size_t index, T val) {
        while (index < tree_.size()) {
            tree_[index] += val;
            index += LowBits(index);
        }
    }

    std::vector<T> tree_;
    std::vector<T> original_nums_;
};
}  // namespace trivial

#endif