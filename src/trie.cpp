#include "trivial/trie.h"

#include "cassert"

namespace trivial {
KVStatus Trie::Get(const Key &key, Value *val) {
    Trie *node = this->SearchPrefix(key);
    if (node == nullptr || !node->is_key_) {
        return KVStatus::NOT_FOUND;
    }
    assert(node->val_ != nullptr);
    if (val != nullptr) {
        *val = *node->val_;
    }
    return KVStatus::OK;
}

void Trie::Set(const Key &key, const Value &val) {
    Trie *node = this;
    for (char ch : key) {
        assert(ch >= 0 && ch < TRIE_ONE_LEVEL_CAP);
        if (node->children_[ch] == nullptr) {
            node->children_[ch] = new Trie();
        }
        node = node->children_[ch];
    }
    node->is_key_ = true;
    if (node->val_ == nullptr) {
        node->val_ = new Value(val);
    } else {
        *node->val_ = val;
    }
}

Trie *Trie::SearchPrefix(const Key &prefix) {
    Trie *node = this;
    for (char ch : prefix) {
        assert(ch >= 0 && ch < TRIE_ONE_LEVEL_CAP);
        if (node->children_[ch] == nullptr) {
            return nullptr;
        }
        node = node->children_[ch];
    }
    return node;
}

void Trie::Destruct() {
    if (val_ != nullptr) {
        delete val_;
        val_ = nullptr;
    }
    for (auto child : children_) {
        if (child != nullptr) {
            child->Destruct();
        }
    }
}
}  // namespace trivial
