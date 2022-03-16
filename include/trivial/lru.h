#ifndef LRU_H_
#define LRU_H_

#include <list>
#include <unordered_map>

#include "trivial/kv.h"

namespace trivial {
class LRU : KVStore {
   public:
    LRU(int cap) : KVStore(cap) {}

    KVStatus Get(const Key &key, Value *val) override;

    void Set(const Key &key, const Value &val) override;

   private:
    typedef std::list<std::pair<Key, Value>> dlist;

   private:
    inline void RefreshUsed(const Key &key);

   private:
    dlist list_;
    std::unordered_map<Key, dlist::iterator> map_;
};

}  // namespace trivial

#endif