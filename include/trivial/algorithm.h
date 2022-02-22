#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <type_traits>
#include <vector>

namespace trivial {

/**
 * @brief quick pow algorithem
 * @param a the base number, should be able to be multiplied by it's own type.
 * @param n the index number, should be integral.
 */
template <typename T, typename P>
T QuickPow(T a, typename std::enable_if<std::is_integral<P>::value, P>::type n,
           const T init) {
    T ans = init;
    while (n) {
        if (n & 1) {
            ans = ans * a;
        }
        n >>= 1;
        a = a * a;
    }
    return ans;
}

/**
 * @brief adjust a std::vector to heap array.
 * @param vec the original std::vector.
 * @param l the index where adjustment begins
 * @param r the index where adjustment ends.
 * @param cmp the compare function. If the logic of cmp is 'less than', the heap
 * will be a max-heap.
 */
template <typename T, typename F>
void adjustHeap(std::vector<T> &vec, int l, int r, F cmp) {
    T val = vec[l];
    for (int i = l * 2 + 1; i < r; i = i * 2 + 1) {
        // less than
        if (i + 1 < r && cmp(vec[i], vec[i + 1])) {
            i++;
        }
        // larger than
        if (!cmp(vec[i], val)) {
            vec[l] = vec[i];
            l = i;
        } else {
            break;
        }
    }
    vec[l] = val;
}

/**
 * @brief heap sort algorithm
 * @param vec the std::vector to be sorted.
 * @param cmp the compare function. If the logic of cmp is 'less than', the sort
 * result will be asending.
 */
template <typename T, typename F>
void HeapSort(std::vector<T> &vec, F cmp) {
    for (int i = vec.size() / 2 - 1; i >= 0; i--) {
        adjustHeap(vec, i, vec.size(), cmp);
    }
    for (int i = vec.size() - 1; i > 0; i--) {
        std::swap(vec[0], vec[i]);
        adjustHeap(vec, 0, i, cmp);
    }
}

}  // namespace trivial

#endif