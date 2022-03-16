#include "trivial/lru.h"

#include "gtest/gtest.h"

namespace trivial {

const static KVStatus OK = KVStatus::OK;
const static KVStatus NOT_FOUND = KVStatus::NOT_FOUND;

TEST(LRUTest, SimpleTest) {
    LRU lru(2);
    lru.Set("1", "1");
    lru.Set("2", "2");
    std::string val;
    EXPECT_EQ(OK, lru.Get("1", &val));
    EXPECT_EQ("1", val);
    lru.Set("3", "3");
    EXPECT_EQ(NOT_FOUND, lru.Get("2", nullptr));
    lru.Set("4", "4");
    EXPECT_EQ(NOT_FOUND, lru.Get("1", nullptr));
    EXPECT_EQ(OK, lru.Get("3", &val));
    EXPECT_EQ("3", val);
    EXPECT_EQ(OK, lru.Get("4", &val));
    EXPECT_EQ("4", val);
}

}  // namespace trivial
