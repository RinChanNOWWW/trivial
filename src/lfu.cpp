#include "trivial/lfu.h"

namespace trivial {

KVStatus LFU::Get(const Key& key, Value* val) {
    if (kvs_.count(key) == 0) {
        return KVStatus::NOT_FOUND;
    }
    IncrFreq(key);
    if (val != nullptr) {
        *val = kvs_[key];
    }
    return KVStatus::OK;
}

void LFU::Set(const Key& key, const Value& val) {
    if (map_.count(key) == 0) {
        // remove a least freq used elem for room
        if (kvs_.size() == cap_) {
            // find the least freq elem
            auto iter = list_.begin();
            auto key_to_remove = *iter->first.begin();
            iter->first.erase(key_to_remove);
            if (iter->first.empty()) {
                list_.erase(iter);
            }
            map_.erase(key_to_remove);
            kvs_.erase(key_to_remove);
        }
        // add new elem
        if (list_.empty() || list_.begin()->second > 1) {
            std::unordered_set<Key> s({key});
            list_.emplace_front(s, 1);
        } else {
            list_.begin()->first.emplace(key);
        }
        map_[key] = list_.begin();
    } else {
        IncrFreq(key);
    }
    kvs_[key] = val;
}

// Prerequisite: key is already exist.
void LFU::IncrFreq(const Key& key) {
    auto cur = map_[key], nxt = next(cur);
    if (nxt == list_.end() || nxt->second > cur->second + 1) {
        std::unordered_set<Key> s({key});
        map_[key] = list_.emplace(nxt, s, cur->second + 1);
    } else {
        // cur.freq == nxt.freq
        nxt->first.emplace(key);
        map_[key] = nxt;
    }
    cur->first.erase(key);
    if (cur->first.empty()) {
        list_.erase(cur);
    }
}

}  // namespace trivial
