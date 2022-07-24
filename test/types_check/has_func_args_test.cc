#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <vector>

#include "lodash/lodash.h"
#include "lodash/types_check/has_func_args.h"

namespace lodash::test {

class HasFuncArgsTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(HasFuncArgsTest, has_func_args) {
    {
        auto f = []([[maybe_unused]] int& x) {};

        {
            auto res = types_check::has_func_args_1<decltype(f), int&>;
            EXPECT_TRUE(res);
        }

        {
            auto res = types_check::has_func_args_2<decltype(f), int&, size_t>;
            EXPECT_FALSE(res);
        }
    }

    {
        auto f = []([[maybe_unused]] int& x, [[maybe_unused]] size_t ix) {};

        {
            auto res = types_check::has_func_args_2<decltype(f), int&, size_t>;
            EXPECT_TRUE(res);
        }

        {
            auto res = types_check::has_func_args_1<decltype(f), int&>;
            EXPECT_FALSE(res);
        }
    }
}

}  // namespace lodash::test
