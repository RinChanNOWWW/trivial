#include "trivial/strings.h"

#include "gtest/gtest.h"

namespace trivial {

TEST(StringsTest, Join) {
    // join vec of int
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        std::string joined = JoinVector(vec, "---");
        ASSERT_EQ("1---2---3---4---5", joined);
    }

    // join vec of char
    {
        std::vector<char> vec{'a', 'b', 'c'};
        std::string joined = JoinVector(vec, " ");
        ASSERT_EQ("a b c", joined);
    }

    // join vec of string
    {
        std::vector<std::string> vec{"aa", "bb", "cc"};
        std::string joined = JoinVector(vec, "|");
        ASSERT_EQ("aa|bb|cc", joined);
    }
}

TEST(StringsTest, Split) {
    struct TestCase {
        std::string to_split;
        std::string delim;
        std::vector<std::string> splited;
    };

    std::vector<TestCase> test_cases = {
        {"123.321.asdsad", ".", {"123", "321", "asdsad"}},
        {"aaa<=>bbb<=>ccc", "<=>", {"aaa", "bbb", "ccc"}},
    };

    for (auto &t : test_cases) {
        auto splited = Split(t.to_split, t.delim);
        ASSERT_EQ(t.splited, splited);
    }
}

TEST(StringsTest, LTrim) {
    // trim with string
    {
        struct TestCase {
            std::string to_trim;
            std::string ws;
            std::string trimed;
        };
        std::vector<TestCase> test_cases = {{"   aaaaa    ", " ", "aaaaa    "},
                                            {"aaabbbaaa", "a", "bbbaaa"},
                                            {"aaabbbaaa", "aa", "bbbaaa"},
                                            {"aaabbbaaa", "A", "aaabbbaaa"}};

        for (auto &t : test_cases) {
            ASSERT_EQ(t.trimed, LTrim(t.to_trim, t.ws));
        }
    }
    // trim with chars
    {
        struct TestCase {
            std::string to_trim;
            const char *ws;
            std::string trimed;
        };
        std::vector<TestCase> test_cases = {{"   aaaaa    ", " ", "aaaaa    "},
                                            {"aaabbbaaa", "a", "bbbaaa"},
                                            {"aaabbbaaa", "aa", "bbbaaa"},
                                            {"aaabbbaaa", "A", "aaabbbaaa"}};
        for (auto &t : test_cases) {
            ASSERT_EQ(t.trimed, LTrim(t.to_trim, t.ws));
        }
    }
    // trim with char
    {
        struct TestCase {
            std::string to_trim;
            char ws;
            std::string trimed;
        };
        std::vector<TestCase> test_cases = {{"   aaaaa    ", ' ', "aaaaa    "},
                                            {"aaabbbaaa", 'a', "bbbaaa"},
                                            {"aaabbbaaa", 'A', "aaabbbaaa"}};
        for (auto &t : test_cases) {
            ASSERT_EQ(t.trimed, LTrim(t.to_trim, t.ws));
        }
    }
}

TEST(StringsTest, RTrim) {
    // trim with string
    {
        struct TestCase {
            std::string to_trim;
            std::string ws;
            std::string trimed;
        };
        std::vector<TestCase> test_cases = {{"   aaaaa    ", " ", "   aaaaa"},
                                            {"aaabbbaaa", "a", "aaabbb"},
                                            {"aaabbbaaa", "aa", "aaabbb"},
                                            {"aaabbbaaa", "A", "aaabbbaaa"}};

        for (auto &t : test_cases) {
            ASSERT_EQ(t.trimed, RTrim(t.to_trim, t.ws));
        }
    }
    // trim with chars
    {
        struct TestCase {
            std::string to_trim;
            const char *ws;
            std::string trimed;
        };
        std::vector<TestCase> test_cases = {{"   aaaaa    ", " ", "   aaaaa"},
                                            {"aaabbbaaa", "a", "aaabbb"},
                                            {"aaabbbaaa", "aa", "aaabbb"},
                                            {"aaabbbaaa", "A", "aaabbbaaa"}};
        for (auto &t : test_cases) {
            ASSERT_EQ(t.trimed, RTrim(t.to_trim, t.ws));
        }
    }
    // trim with char
    {
        struct TestCase {
            std::string to_trim;
            char ws;
            std::string trimed;
        };
        std::vector<TestCase> test_cases = {{"   aaaaa    ", ' ', "   aaaaa"},
                                            {"aaabbbaaa", 'a', "aaabbb"},
                                            {"aaabbbaaa", 'A', "aaabbbaaa"}};
        for (auto &t : test_cases) {
            ASSERT_EQ(t.trimed, RTrim(t.to_trim, t.ws));
        }
    }
}

TEST(StringsTest, Trim) {
    // trim with string
    {
        struct TestCase {
            std::string to_trim;
            std::string ws;
            std::string trimed;
        };
        std::vector<TestCase> test_cases = {{"   aaaaa    ", " ", "aaaaa"},
                                            {"aaabbbaaa", "a", "bbb"},
                                            {"aaabbbaaa", "aa", "bbb"},
                                            {"aaabbbaaa", "A", "aaabbbaaa"}};

        for (auto &t : test_cases) {
            ASSERT_EQ(t.trimed, Trim(t.to_trim, t.ws));
        }
    }
    // trim with chars
    {
        struct TestCase {
            std::string to_trim;
            const char *ws;
            std::string trimed;
        };
        std::vector<TestCase> test_cases = {{"   aaaaa    ", " ", "aaaaa"},
                                            {"aaabbbaaa", "a", "bbb"},
                                            {"aaabbbaaa", "aa", "bbb"},
                                            {"aaabbbaaa", "A", "aaabbbaaa"}};
        for (auto &t : test_cases) {
            ASSERT_EQ(t.trimed, Trim(t.to_trim, t.ws));
        }
    }
    // trim with char
    {
        struct TestCase {
            std::string to_trim;
            char ws;
            std::string trimed;
        };
        std::vector<TestCase> test_cases = {{"   aaaaa    ", ' ', "aaaaa"},
                                            {"aaabbbaaa", 'a', "bbb"},
                                            {"aaabbbaaa", 'A', "aaabbbaaa"}};
        for (auto &t : test_cases) {
            ASSERT_EQ(t.trimed, Trim(t.to_trim, t.ws));
        }
    }
}

}  // namespace trivial