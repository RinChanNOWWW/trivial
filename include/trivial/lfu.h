#ifndef LFU_H_
#define LFU_H_

#include <list>
#include <unordered_map>
#include <unordered_set>

#include "trivial/kv.h"

namespace trivial {

class LFU : KVStore {
   public:
    LFU(int cap) : KVStore(cap) {}

    KVStatus Get(const Key &key, Value *val) override;

    void Set(const Key &key, const Value &val) override;

   private:
    typedef std::list<std::pair<std::unordered_set<Key>, int>> dlist;

   private:
    void IncrFreq(const Key &key);

   private:
    dlist list_;
    std::unordered_map<Key, dlist::iterator> map_;
    std::unordered_map<Key, Value> kvs_;
};

}  // namespace trivial

#endif