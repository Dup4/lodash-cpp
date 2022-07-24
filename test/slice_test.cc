#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <vector>

#include "lodash/lodash.h"

namespace lodash::test {

class SliceTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(SliceTest, map_test) {
    auto t = std::vector<int>({1, 2, 3, 4, 5});

    {
        auto res = Map<std::vector<int>>(t, [](auto &&x) {
            return x * 2;
        });

        EXPECT_EQ(res, std::vector<int>({2, 4, 6, 8, 10}));
    }

    {
        auto res = Map<std::vector<std::string>>(t, [](auto &&x) {
            return std::to_string(x);
        });

        EXPECT_EQ(res, std::vector<std::string>({"1", "2", "3", "4", "5"}));
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
        EXPECT_TRUE(types_check::is_map<decltype(mp)>);

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

TEST_F(SliceTest, Every) {
    {
        auto t = std::vector<int>({1, 2, 3, 4, 5});

        {
            auto res = EveryBy(t, [](const int &x) {
                return x > 0;
            });

            EXPECT_TRUE(res);
        }

        {
            auto res = EveryBy(t, [](const int &x) {
                return x > 1;
            });

            EXPECT_FALSE(res);
        }

        {
            auto res = Every(t);
            EXPECT_TRUE(res);
        }
    }

    {
        auto t = std::map<int, int>({{1, 1}, {2, 2}, {3, 3}});

        {
            auto res = EveryBy(t, [](const int k, const int &v) {
                return k >= 1 && v >= 1;
            });

            EXPECT_TRUE(res);
        }
    }
}

TEST_F(SliceTest, Some) {
    {
        auto t = std::vector<int>({1, 2, 3, 4, 5});

        {
            auto res = SomeBy(t, [](const int &x) {
                return x > 0;
            });

            EXPECT_TRUE(res);
        }

        {
            auto res = SomeBy(t, [](const int &x) {
                return x > 1;
            });

            EXPECT_TRUE(res);
        }

        {
            auto res = Some(t);
            EXPECT_TRUE(res);
        }
    }

    {
        auto t = std::map<int, int>({{1, 1}, {2, 2}, {3, 3}});

        {
            auto res = SomeBy(t, [](const int k, const int &v) {
                return k >= 3 && v >= 3;
            });

            EXPECT_TRUE(res);
        }

        {
            auto res = SomeBy(t, [](const int k, const int &v) {
                return k >= 4 && v >= 4;
            });

            EXPECT_FALSE(res);
        }
    }
}

}  // namespace lodash::test
