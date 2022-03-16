#include "trivial/lfu.h"

#include "gtest/gtest.h"

namespace trivial {

const static KVStatus OK = KVStatus::OK;
const static KVStatus NOT_FOUND = KVStatus::NOT_FOUND;

TEST(LFUTest, SimpleTest) {
    LFU lfu(2);
    lfu.Set("1", "1");
    lfu.Set("2", "2");
    std::string val;
    EXPECT_EQ(OK, lfu.Get("1", &val));
    EXPECT_EQ("1", val);
    lfu.Set("3", "3");
    EXPECT_EQ(NOT_FOUND, lfu.Get("2", nullptr));
    lfu.Set("4", "4");
    EXPECT_EQ(NOT_FOUND, lfu.Get("3", nullptr));
    EXPECT_EQ(OK, lfu.Get("1", &val));
    EXPECT_EQ("1", val);
    EXPECT_EQ(OK, lfu.Get("4", &val));
    EXPECT_EQ("4", val);
}

}  // namespace trivial