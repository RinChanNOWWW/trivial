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

TEST(TrieTest, IterTest) {
    Trie *trie = new Trie();

    trie->Set("abc", "");
    trie->Set("abcd", "");
    trie->Set("abe", "");
    trie->Set("ac", "");
    trie->Set("b", "");

    // seek from beigin
    TrieIterator iter(trie);
    iter.SeekToFirst();
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("abc", iter.GetKey());
    iter.Next();
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("abcd", iter.GetKey());
    iter.Next();
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("abe", iter.GetKey());
    iter.Next();
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("ac", iter.GetKey());
    iter.Next();
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("b", iter.GetKey());
    iter.Next();
    EXPECT_FALSE(iter.IsValid());

    // seek from an exist key
    iter.Seek("abe");
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("abe", iter.GetKey());
    iter.Next();
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("ac", iter.GetKey());
    iter.Next();
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("b", iter.GetKey());
    iter.Next();
    EXPECT_FALSE(iter.IsValid());

    // seek from a non-exist key which is in the trie
    iter.Seek("ab");
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("abc", iter.GetKey());
    iter.Next();
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("abcd", iter.GetKey());
    iter.Next();
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("abe", iter.GetKey());
    iter.Next();
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("ac", iter.GetKey());
    iter.Next();
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("b", iter.GetKey());
    iter.Next();
    EXPECT_FALSE(iter.IsValid());

    // seek from a non-exist key which is not in the trie
    iter.Seek("abdf");
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("abe", iter.GetKey());
    iter.Next();
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("ac", iter.GetKey());
    iter.Next();
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("b", iter.GetKey());
    iter.Next();
    EXPECT_FALSE(iter.IsValid());

    // seek from a non-exist key which is greater than the last key
    iter.Seek("ba");
    EXPECT_FALSE(iter.IsValid());

    // seek randomly
    iter.Seek("abe");
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("abe", iter.GetKey());
    iter.Seek("abc");
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("abc", iter.GetKey());
    iter.Seek("ac");
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("ac", iter.GetKey());
    iter.Seek("b");
    EXPECT_TRUE(iter.IsValid());
    EXPECT_EQ("b", iter.GetKey());
    iter.Next();
    EXPECT_FALSE(iter.IsValid());

    delete trie;
}

}  // namespace trivial
