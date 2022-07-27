#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <map>
#include <string>
#include <vector>

#include "lodash/lodash.h"

namespace lodash::test {

class MathTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(MathTest, Range) {
    {
        auto t = Range(10);
        auto expected = std::vector<int32_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        EXPECT_EQ(t, expected);
    }

    {
        auto t = Range(-10);
        auto expected = std::vector<int32_t>{0, -1, -2, -3, -4, -5, -6, -7, -8, -9};
        EXPECT_EQ(t, expected);
    }

    {
        auto t = Range(10, 20);
        auto expected = std::vector<int32_t>{10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
        EXPECT_EQ(t, expected);
    }

    {
        auto t = Range(20, 10);
        auto expected = std::vector<int32_t>{20, 19, 18, 17, 16, 15, 14, 13, 12, 11};
        EXPECT_EQ(t, expected);
    }

    {
        auto t = Range(10, 20, 5);
        auto expected = std::vector<int32_t>{10, 15};
        EXPECT_EQ(t, expected);
    }

    {
        auto t = Range(20, 10, -5);
        auto expected = std::vector<int32_t>{20, 15};
        EXPECT_EQ(t, expected);
    }

    {
        auto t = Range(int64_t(3e9), int64_t(3e9 + 10));
        auto expected = std::vector<int64_t>({
                3000000000,
                3000000001,
                3000000002,
                3000000003,
                3000000004,
                3000000005,
                3000000006,
                3000000007,
                3000000008,
                3000000009,
        });
        EXPECT_EQ(t, expected);
    }

    {
        int32_t res = 0;
        for (const auto& ix : Range(10)) {
            res += ix;
        }
        EXPECT_EQ(res, 45);
    }
}

TEST_F(MathTest, Clamp) {
    EXPECT_EQ(Clamp(0, 0, 1), 0);
    EXPECT_EQ(Clamp(0, 1, 2), 1);
    EXPECT_EQ(Clamp(1, 0, 2), 1);
    EXPECT_EQ(Clamp(1, 1, 2), 1);
    EXPECT_EQ(Clamp(2, 0, 2), 2);
    EXPECT_EQ(Clamp(2, 1, 2), 2);
    EXPECT_EQ(Clamp(3, 0, 2), 2);
}

TEST_F(MathTest, Sum) {
    {
        auto t = std::vector<int>({1, 2, 3, 4, 5});
        EXPECT_EQ(Sum(t), 15);
    }

    {
        auto t = std::vector<int>({1, 2, 3, 4, 5});
        EXPECT_EQ(SumBy(t,
                        [](int v) {
                            return v * v;
                        }),
                  55);
    }
}

}  // namespace lodash::test
