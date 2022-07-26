#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <map>
#include <string>
#include <vector>

#include "lodash/lodash.h"

namespace lodash::test {

class IntersectTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(IntersectTest, Contains) {
    {
        auto t = std::vector<int>({1, 2, 3, 4, 5, 6});

        {
            auto res = Contains(t, 3);
            EXPECT_TRUE(res);
        }

        {
            auto res = ContainsBy(t, [](auto &&x) {
                return x > 3;
            });
            EXPECT_TRUE(res);
        }
    }
}

TEST_F(IntersectTest, Every) {
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

TEST_F(IntersectTest, Some) {
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

TEST_F(IntersectTest, None) {
    {
        auto t = std::vector<int>({1, 2, 3, 4, 5});

        {
            auto res = None(t);
            EXPECT_FALSE(res);
        }

        {
            auto res = NoneBy(t, [](const int &x) {
                return x <= 0;
            });
            EXPECT_TRUE(res);
        }

        {
            auto res = NoneBy(t, [](const int &x) {
                return x <= 1;
            });
            EXPECT_FALSE(res);
        }
    }
}

}  // namespace lodash::test
