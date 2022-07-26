#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <map>
#include <vector>

#include "lodash/lodash.h"

namespace lodash::test {

class SliceTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(SliceTest, Map) {
    const auto t = std::vector<int>({1, 2, 3, 4, 5});

    {
        auto res = Map(t, [](auto &&x) {
            return x * 2;
        });

        EXPECT_EQ(res, std::vector<int>({2, 4, 6, 8, 10}));
    }

    {
        auto res = Map(t, [](auto &&x) {
            return std::to_string(x);
        });

        EXPECT_EQ(res, std::vector<std::string>({"1", "2", "3", "4", "5"}));
    }

    {
        auto res = Map<std::map<int, int>>(t, [](auto &&x, size_t ix) {
            return std::make_pair(ix, x);
        });

        auto expected = std::map<int, int>({{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}});
        EXPECT_EQ(res, expected);
    }
}

TEST_F(SliceTest, Reduce) {
    {
        auto t = std::vector<int>({1, 2, 3, 4, 5});

        {
            auto res = Reduce(
                    t,
                    [](const int &pre, const int &v) {
                        return pre + v;
                    },
                    0);

            EXPECT_EQ(res, 15);
        }

        {
            auto res = Reduce(
                    t,
                    [](const int &pre, const int &v) {
                        return pre + v;
                    },
                    10);
            EXPECT_EQ(res, 25);
        }

        {
            auto res = Reduce(
                    t,
                    [](const std::string &pre, const int &v) {
                        return pre + std::to_string(v);
                    },
                    std::string(""));
            EXPECT_EQ(res, "12345");
        }
    }

    {
        auto t = std::map<int, int>({{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}});
        auto res = Reduce(
                t,
                [](const int &pre, const int &k, const int &v) {
                    return pre + k + v;
                },
                0);
        EXPECT_EQ(res, 30);
    }
}

TEST_F(SliceTest, Filter) {
    {
        const auto t = std::vector<int>({1, 2, 3, 4, 5});

        auto res = Filter(t, [](auto &&x) {
            return x % 2 == 0;
        });

        EXPECT_EQ(res, std::vector<int>({2, 4}));
    }

    {
        const auto t = std::map<int, int>({{1, 2}, {2, 3}, {3, 4}, {4, 5}});

        auto res = Filter(t, [](const int &k, const int &v) {
            return k >= 3 || v >= 3;
        });

        auto expected = std::map<int, int>({{2, 3}, {3, 4}, {4, 5}});
        EXPECT_EQ(res, expected);
    }
}

TEST_F(SliceTest, Reject) {
    {
        auto t = std::vector<int>({1, 2, 3, 4, 5});
        auto res = Reject(t, [](auto &&x) {
            return x % 2 == 0;
        });
        auto expected = std::vector<int>({1, 3, 5});
        EXPECT_EQ(res, expected);
    }
}

TEST_F(SliceTest, ForEach) {
    {
        auto x = std::vector<int>({1, 2, 3, 4, 5});
        ForEach(x, [](int &x) {
            ++x;
        });

        EXPECT_EQ(x, std::vector<int>({2, 3, 4, 5, 6}));
    }

    {
        auto x = std::vector<int>({1, 2, 3, 4, 5});
        ForEach(x, [](int &x, size_t ix) {
            x += static_cast<int>(ix);
        });

        EXPECT_EQ(x, std::vector<int>({1, 3, 5, 7, 9}));
    }

    {
        auto x = std::vector<int>({1, 2, 3, 4, 5});
        ForEach(x, []([[maybe_unused]] const int &x) {});

        EXPECT_EQ(x, std::vector<int>({1, 2, 3, 4, 5}));
    }

    {
        auto x = std::set<int>({1, 2, 3});
        ForEach(x, [](int x) {
            ++x;
        });

        EXPECT_EQ(x, std::set<int>({1, 2, 3}));
    }

    {
        std::string s = "abcd";
        ForEach(s, [](char &c) {
            ++c;
        });

        EXPECT_EQ(s, std::string("bcde"));
    }

    {
        auto mp = std::map<int, int>({{1, 1}, {2, 2}, {3, 3}});
        EXPECT_TRUE(type_check::is_map<decltype(mp)>);

        int ix = 0;

        {
            ForEach(mp, [&ix](auto &kv) {
                ++ix;
                kv.second += kv.first;
            });

            auto expected = std::map<int, int>({{1, 2}, {2, 4}, {3, 6}});
            EXPECT_EQ(mp, expected);
            EXPECT_EQ(ix, 3);
        }

        {
            ForEach(mp, [&ix](const int &k, int &v) {
                ++ix;
                v += k;
            });

            auto expected = std::map<int, int>({{1, 3}, {2, 6}, {3, 9}});
            EXPECT_EQ(mp, expected);
            EXPECT_EQ(ix, 6);
        }

        {
            ForEach(mp, [&ix](const int &k, int &v, size_t _ix) {
                ++ix;
                v += k;
                v += int(_ix);
            });

            auto expected = std::map<int, int>({{1, 4}, {2, 9}, {3, 14}});
            EXPECT_EQ(mp, expected);
            EXPECT_EQ(ix, 9);
        }
    }
}

TEST_F(SliceTest, Flatten) {
    {
        auto t = std::vector<std::vector<int>>({{1, 2}, {3, 4}, {5, 6}});
        auto res = Flatten(t);
        auto expected = std::vector<int>({1, 2, 3, 4, 5, 6});
        EXPECT_EQ(res, expected);
    }

    {
        auto t = std::vector<std::vector<std::vector<int>>>({{{1, 2}, {3, 4}}, {{5, 6}}});
        auto res = Flatten(t);
        auto expected = std::vector<int>({1, 2, 3, 4, 5, 6});
        EXPECT_EQ(res, expected);
    }
}

TEST_F(SliceTest, Times) {
    {
        auto res = Times(3, [](size_t ix) {
            return ix;
        });
        auto expected = std::vector<size_t>({0, 1, 2});
        EXPECT_EQ(res, expected);
    }

    {
        auto res = Times(5, [](size_t ix) {
            return std::to_string(ix);
        });
        auto expected = std::vector<std::string>({"0", "1", "2", "3", "4"});
        EXPECT_EQ(res, expected);
    }
}

TEST_F(SliceTest, Uniq) {
    {
        auto t = std::vector<int>({1, 1, 2, 2, 3, 3, 4, 4, 5, 5});
        auto res = Uniq(t);
        auto expected = std::vector<int>({1, 2, 3, 4, 5});
        EXPECT_EQ(res, expected);
    }

    {
        auto t = std::vector<int>({2, 2, 3, 3, 1, 1, 5, 5, 4, 4});
        auto res = Uniq(t);
        auto expected = std::vector<int>({2, 3, 1, 5, 4});
        EXPECT_EQ(res, expected);
    }
}

TEST_F(SliceTest, UniqBy) {
    {
        auto t = std::vector<int>({1, 2, 3, 4, 5});
        auto res = UniqBy(t, [](auto &&x) {
            return x % 2;
        });
        auto expected = std::vector<int>({1, 2});
        EXPECT_EQ(res, expected);
    }
}

TEST_F(SliceTest, Count) {
    {
        auto t = std::vector<int>({1, 1, 2, 2, 3, 4, 5});

        {
            auto res = CountBy(t, [](const int &x) {
                return x > 0;
            });

            EXPECT_EQ(res, 7);
        }

        {
            auto res = CountBy(t, [](const int &x) {
                return x > 1;
            });

            EXPECT_EQ(res, 5);
        }

        {
            auto res = Count(t, 2);
            EXPECT_EQ(res, 2);
        }
    }
}

TEST_F(SliceTest, Replace) {
    {
        auto t = std::vector<int>({1, 2, 3, 4, 5, 4, 3, 2, 1});
        auto res = Replace(t, 4, 0);
        auto expected = std::vector<int>({1, 2, 3, 0, 5, 0, 3, 2, 1});
        EXPECT_EQ(res, expected);
    }

    {
        auto t = std::string("abcdcba");
        auto res = Replace(t, 'a', 'c');
        auto expected = std::string("cbcdcbc");
        EXPECT_EQ(res, expected);
    }
}

TEST_F(SliceTest, Compact) {
    {
        auto t = std::vector<int>({0, 1, 2, 3, 0, 5, 6});
        auto res = Compact(t);
        auto expected = std::vector<int>({1, 2, 3, 5, 6});
        EXPECT_EQ(res, expected);
    }

    {
        auto t = std::vector<std::string>({"", "1", "", "2", "", "3"});
        auto res = Compact(t);
        auto expected = std::vector<std::string>({"1", "2", "3"});
        EXPECT_EQ(res, expected);
    }
}

}  // namespace lodash::test
