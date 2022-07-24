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
        ForEach(x, [](int &x) {
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
}

}  // namespace lodash::test
