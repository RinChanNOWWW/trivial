#ifndef TRIE_H_
#define TRIE_H_

#include <array>
#include <cassert>
#include <stack>

#include "kv.h"
#include "kv_iterator.h"

#define TRIE_ONE_LEVEL_CAP 256

namespace trivial {

class TrieIterator;

class Trie : public KVStore {
   public:
    Trie() : is_key_(false), val_(nullptr) { children_.fill(nullptr); }

    KVStatus Get(const Key &key, Value *val) override;

    void Set(const Key &key, const Value &val) override;

    ~Trie() { this->Destruct(); }

   private:
    Trie *SearchPrefix(const Key &prefix);

    void Destruct();

   private:
    typedef std::array<Trie *, TRIE_ONE_LEVEL_CAP> Children;
    // only support ASCII now.
    Children children_;
    bool is_key_;
    Value *val_;
    friend TrieIterator;
};

class TrieIterator : public KVIterator {
   public:
    TrieIterator(const TrieIterator &) = delete;
    TrieIterator(TrieIterator &&) = delete;

   public:
    TrieIterator(Trie *trie) : trie_(trie) {}

    bool IsValid() const override { return !iters_.empty(); }

    void Seek(const Key &start_key) override;

    void SeekToFirst() override;

    void Next() override;

    Key GetKey() const override {
        assert(IsValid());
        auto it = iters_.top().second;
        assert(it && (*it));
        assert((*it)->is_key_);
        return current_key_;
    }
    Value GetValue() const override {
        assert(IsValid());
        const auto it = iters_.top().second;
        assert(it && (*it));
        assert((*it)->is_key_);
        assert((*it)->val_ != nullptr);
        return *(*it)->val_;
    }

    void Clear() {
        current_key_.clear();
        while (!iters_.empty()) {
            iters_.pop();
        }
    }

   private:
    // Seek for key from the begin of cur by dfs. Return if key is found
    bool SeekFromBegin(Trie *cur, const Key &key);

    // Seek for key forwards from curretion position. Return if key is found
    // REQUIRES: IsValid() and key >= current_key_
    void SeekForward(const Key &key);

   private:
    Trie *trie_;
    // trace the position at each level
    std::stack<std::pair<Trie *, Trie::Children::iterator>> iters_;

    Key current_key_;
};

}  // namespace trivial

#endif