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
