#include "trivial/trie.h"

#include <cassert>

#define ASSERT_CHAR_VALID(ch) (assert(ch >= 0 && ch < TRIE_ONE_LEVEL_CAP))

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
        ASSERT_CHAR_VALID(ch);
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
        ASSERT_CHAR_VALID(ch);
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

void TrieIterator::Seek(const Key &start_key) {
    if (!IsValid() || GetKey() > start_key) {
        Clear();
        SeekFromBegin(trie_, start_key);
    } else {
        SeekForward(start_key);
    }
}

bool TrieIterator::SeekFromBegin(Trie *cur, const Key &key) {
    assert(cur != nullptr);

    if (cur->is_key_ && current_key_ >= key) {
        return true;
    }

    // prune
    int i = 0, j = 0;
    while (i < current_key_.length() && j < key.length() &&
           current_key_[i] == key[j]) {
        i++;
        j++;
    }
    if (i < current_key_.length() && j < key.length() &&
        current_key_[i] < key[j]) {
        return false;
    }

    for (auto it = cur->children_.begin(); it != cur->children_.end(); it++) {
        if ((*it) != nullptr) {
            current_key_.push_back(it - cur->children_.begin());
            iters_.emplace(cur, it);
            bool found = SeekFromBegin((*it), key);
            if (found) {
                return true;
            }
            iters_.pop();
            current_key_.pop_back();
        }
    }
    return false;
}

void TrieIterator::SeekToFirst() { SeekFromBegin(trie_, ""); }

void TrieIterator::SeekForward(const Key &key) {
    assert(IsValid());
    assert(GetKey() <= key);
    if (GetKey() == key) {
        return;
    }
    bool has_search_last_level_totally = false;
    while (!iters_.empty()) {
        auto parent = iters_.top().first;
        auto cur = iters_.top().second;
        assert(parent);
        assert(cur && *cur);
        if ((*cur)->is_key_ && current_key_ >= key) {
            return;
        }
        // First, search children
        if (!has_search_last_level_totally && SeekFromBegin(*cur, key)) {
            return;
        }
        // Second, search siblings
        for (auto sibling = cur + 1; sibling != parent->children_.end();
             sibling++) {
            if ((*sibling) != nullptr) {
                iters_.top().second = sibling;
                current_key_.back() = sibling - parent->children_.begin();
                if (SeekFromBegin(*sibling, key)) {
                    return;
                }
            }
        }
        has_search_last_level_totally = true;
        // Third, pop iters_
        iters_.pop();
        current_key_.pop_back();
    }
}

void TrieIterator::Next() {
    Key next_key = current_key_;
    next_key.push_back(1);
    SeekForward(next_key);
}
}  // namespace trivial
