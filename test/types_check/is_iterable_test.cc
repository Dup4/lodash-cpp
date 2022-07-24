#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <map>
#include <vector>

#include "lodash/lodash.h"
#include "lodash/types_check/is_iterable.h"

namespace lodash::test {

class IsIterableTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(IsIterableTest, is_iterable) {
    EXPECT_TRUE(types_check::is_iterable<std::vector<int>>);

    {
        auto res = types_check::is_iterable<std::map<int, int>>;
        EXPECT_TRUE(res);
    }

    EXPECT_FALSE(types_check::is_iterable<int>);
}

}  // namespace lodash::test
