#include "trivial/lru.h"

namespace trivial {

KVStatus LRU::Get(const Key &key, Value *val) {
    if (map_.count(key) == 0) {
        return KVStatus::NOT_FOUND;
    }
    RefreshUsed(key);
    if (val != nullptr) {
        // if val is nullptr, just refresh the lru.
        *val = map_[key]->second;
    }
    return KVStatus::OK;
}

void LRU::Set(const Key &key, const Value &val) {
    if (map_.count(key) == 0) {
        list_.emplace_front(key, val);
        map_[key] = list_.begin();
        if (list_.size() > cap_) {
            map_.erase(list_.back().first);
            list_.pop_back();
        }
    } else {
        RefreshUsed(key);
        map_[key]->second = val;
    }
}

void LRU::RefreshUsed(const Key &key) {
    auto iter = map_[key];
    list_.erase(iter);
    list_.emplace_front(iter->first, iter->second);
    map_[key] = list_.begin();
}

}  // namespace trivial
