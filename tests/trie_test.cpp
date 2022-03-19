#include "trivial/trie.h"

#include "gtest/gtest.h"

namespace trivial {

TEST(TrieTest, SimpleTest) {
    Trie *trie = new Trie();
    EXPECT_EQ(KVStatus::NOT_FOUND, trie->Get("k", nullptr));
    std::string val;
    trie->Set("k1", "v1");
    EXPECT_EQ(KVStatus::OK, trie->Get("k1", &val));
    EXPECT_EQ("v1", val);
    trie->Set("k2", "v2");
    EXPECT_EQ(KVStatus::OK, trie->Get("k2", &val));
    EXPECT_EQ("v2", val);
    trie->Set("k3", "v3");
    EXPECT_EQ(KVStatus::OK, trie->Get("k3", &val));
    EXPECT_EQ("v3", val);
    trie->Set("k3", "new_v3");
    EXPECT_EQ(KVStatus::OK, trie->Get("k3", &val));
    EXPECT_EQ("new_v3", val);
    delete trie;
}

}  // namespace trivial
