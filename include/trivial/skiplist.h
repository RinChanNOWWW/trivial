#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include <atomic>
#include <cassert>
#include <random>

namespace trivial {
template <typename Key, class Comparator>
class SkipList {
   private:
    struct Node;

   public:
    SkipList(Comparator cmp);

    void Insert(const Key& key);

    bool Contains(const Key& key) const;

    class Iterator {
       public:
        explicit Iterator(const SkipList* list);

        bool Valid() const;

        const Key& key() const;

        void Next();

        void Prev();

        void Seek(const Key& target);

        void SeekToFirst();

        void SeekToLast();

       private:
        const SkipList* list_;
        Node* node_;
    };

   private:
    enum { kMaxHeight = 12 };

    inline int GetMaxHeight() const {
        return max_height_.load(std::memory_order_relaxed);
    }

    Node* NewNode(const Key& key, int height);

    int RandomHeight();

    bool Equal(const Key& a, const Key& b) const { return compare_(a, b) == 0; }

    bool KeyIsAfterNode(const Key& key, Node* n) const;

    Node* FindGreaterOrEqual(const Key& key, Node** prev) const;

    Node* FindLessThan(const Key& key) const;

    Node* FindLast() const;

    Node* const head_;

    Comparator const compare_;

    std::atomic<int> max_height_;

    std::mt19937 rand_engine_;
};

template <typename Key, class Comparator>
struct SkipList<Key, Comparator>::Node {
    explicit Node(const Key& k) : key(k){};

    Key const key;

    Node* Next(int n) {
        assert(n >= 0);
        return next_[n].load(std::memory_order_acquire);
    }

    void SetNext(int n, Node* x) {
        assert(n >= 0);
        next_[n].store(x, std::memory_order_release);
    }

    Node* NoBarrier_Next(int n) {
        assert(n >= 0);
        return next_[n].load(std::memory_order_relaxed);
    }

    void NoBarrier_SetNext(int n, Node* x) {
        assert(n >= 0);
        next_[n].store(x, std::memory_order_relaxed);
    }

   private:
    std::atomic<Node*> next_[1];
};

template <typename Key, class Comparator>
inline SkipList<Key, Comparator>::Iterator::Iterator(const SkipList* list) {
    list_ = list;
    node_ = nullptr;
}

template <typename Key, class Comparator>
inline bool SkipList<Key, Comparator>::Iterator::Valid() const {
    return node_ != nullptr;
}

template <typename Key, class Comparator>
inline const Key& SkipList<Key, Comparator>::Iterator::key() const {
    assert(Valid());
    return node_->key;
}

template <typename Key, class Comparator>
inline void SkipList<Key, Comparator>::Iterator::Next() {
    assert(Valid());
    node_ = node_->Next(0);
}

template <typename Key, class Comparator>
inline void SkipList<Key, Comparator>::Iterator::Prev() {
    assert(Valid());
    node_ = list_->FindLessThan(node_->key);
    if (node_ == list_->head_) {
        node_ = nullptr;
    }
}

template <typename Key, class Comparator>
inline void SkipList<Key, Comparator>::Iterator::Seek(const Key& target) {
    node_ = list_->FindGreaterOrEqual(target, nullptr);
}

template <typename Key, class Comparator>
inline void SkipList<Key, Comparator>::Iterator::SeekToFirst() {
    node_ = list_->head_->Next(0);
}

template <typename Key, class Comparator>
inline void SkipList<Key, Comparator>::Iterator::SeekToLast() {
    node_ = list_->FindLast();
    if (node_ == list_->head_) {
        node_ = nullptr;
    }
}

template <typename Key, class Comparator>
typename SkipList<Key, Comparator>::Node* SkipList<Key, Comparator>::NewNode(
    const Key& key, int height) {
    char* const node_memory =
        new char[sizeof(Node) + sizeof(std::atomic<Node*>) * (height - 1)];
    return new (node_memory) Node(key);
}

template <typename Key, class Comparator>
int SkipList<Key, Comparator>::RandomHeight() {
    static const unsigned int kBranching = 4;
    int height = 1;
    std::uniform_int_distribution<uint32_t> dis(0, kBranching);
    while (height < kMaxHeight && dis(rand_engine_) == 0) {
        height++;
    }
    assert(height > 0);
    assert(height <= kMaxHeight);
    return height;
}

template <typename Key, class Comparator>
bool SkipList<Key, Comparator>::KeyIsAfterNode(const Key& key, Node* n) const {
    return (n != nullptr) && compare_(n->key, key) < 0;
}

template <typename Key, class Comparator>
typename SkipList<Key, Comparator>::Node*
SkipList<Key, Comparator>::FindGreaterOrEqual(const Key& key,
                                              Node** prev) const {
    Node* x = head_;
    int level = GetMaxHeight() - 1;
    while (true) {
        Node* next = x->Next(level);
        if (KeyIsAfterNode(key, next)) {
            x = next;
        } else {
            if (prev != nullptr) {
                prev[level] = x;
            }
            if (level == 0) {
                return next;
            } else {
                level--;
            }
        }
    }
}

template <typename Key, class Comparator>
typename SkipList<Key, Comparator>::Node*
SkipList<Key, Comparator>::FindLessThan(const Key& key) const {
    Node* x = head_;
    int level = GetMaxHeight() - 1;
    while (true) {
        assert(x == head_ || compare_(x->key, key) < 0);
        Node* next = x->Next(level);
        if (next == nullptr || compare_(next->key, key) >= 0) {
            if (level == 0) {
                return x;
            } else {
                level--;
            }
        } else {
            x = next;
        }
    }
}

template <typename Key, class Comparator>
typename SkipList<Key, Comparator>::Node* SkipList<Key, Comparator>::FindLast()
    const {
    Node* x = head_;
    int level = GetMaxHeight() - 1;
    while (true) {
        Node* next = x->Next(level);
        if (next == nullptr) {
            if (level == 0) {
                return x;
            } else {
                level--;
            }
        } else {
            x = next;
        }
    }
}

template <typename Key, class Comparator>
SkipList<Key, Comparator>::SkipList(Comparator cmp)
    : head_(NewNode(0, kMaxHeight)), max_height_(1), compare_(cmp) {
    for (int i = 0; i < kMaxHeight; i++) {
        head_->SetNext(i, nullptr);
    }
    std::random_device rd;
    const uint32_t sd = rd();
    rand_engine_ = std::mt19937(sd);
}

template <typename Key, class Comparator>
void SkipList<Key, Comparator>::Insert(const Key& key) {
    Node* prev[kMaxHeight];
    Node* x = FindGreaterOrEqual(key, prev);
    assert(x == nullptr || !Equal(key, x->key));
    int height = RandomHeight();
    if (height > GetMaxHeight()) {
        for (int i = GetMaxHeight(); i < height; i++) {
            prev[i] = head_;
        }
        max_height_.store(height, std::memory_order_relaxed);
    }
    x = NewNode(key, height);
    for (int i = 0; i < height; i++) {
        x->NoBarrier_SetNext(i, prev[i]->NoBarrier_Next(i));
        prev[i]->SetNext(i, x);
    }
}

template <typename Key, class Comparator>
bool SkipList<Key, Comparator>::Contains(const Key& key) const {
    Node* x = FindGreaterOrEqual(key, nullptr);
    if (x != nullptr && Equal(key, x->key)) {
        return true;
    }
    return false;
}

}  // namespace trivial

#endif