#ifndef TRIE_H_
#define TRIE_H_

#include <array>

#include "kv.h"

#define TRIE_ONE_LEVEL_CAP 256

namespace trivial {

class Trie : KVStore {
   public:
    Trie() : is_key_(false) {}

    KVStatus Get(const Key &key, Value *val) override;

    void Set(const Key &key, const Value &val) override;

    ~Trie() { this->Destruct(); }

   private:
    Trie *SearchPrefix(const Key &prefix);

    void Destruct();

   private:
    // only support ASCII now.
    std::array<Trie *, TRIE_ONE_LEVEL_CAP> children_;
    bool is_key_;
    Value *val_;
};

}  // namespace trivial

#endif