#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <map>
#include <vector>

#include "lodash/lodash.h"
#include "lodash/type_check/is_iterable.h"

namespace lodash::type_check::test {

class IsIterableTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(IsIterableTest, is_iterable) {
    EXPECT_TRUE(is_iterable<std::vector<int>>);

    {
        auto res = is_iterable<std::map<int, int>>;
        EXPECT_TRUE(res);
    }

    EXPECT_FALSE(is_iterable<int>);
}

}  // namespace lodash::type_check::test
