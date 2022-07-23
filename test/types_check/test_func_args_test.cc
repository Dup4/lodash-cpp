#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <vector>

#include "lodash/lodash.h"
#include "lodash/types_check/test_func_args.h"

namespace lodash::test {

class TestFuncArgsTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(TestFuncArgsTest, test_func_args) {
    {
        auto f = []([[maybe_unused]] int& x) {};

        {
            auto res = types_check::test_func_args_1_v<decltype(f), int&>;
            EXPECT_TRUE(res);
        }

        {
            auto res = types_check::test_func_args_2_v<decltype(f), int&, size_t>;
            EXPECT_FALSE(res);
        }
    }

    {
        auto f = []([[maybe_unused]] int& x, [[maybe_unused]] size_t ix) {};

        {
            auto res = types_check::test_func_args_2_v<decltype(f), int&, size_t>;
            EXPECT_TRUE(res);
        }

        {
            auto res = types_check::test_func_args_1_v<decltype(f), int&>;
            EXPECT_FALSE(res);
        }
    }
}

}  // namespace lodash::test
