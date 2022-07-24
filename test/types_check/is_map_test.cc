#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <map>
#include <vector>

#include "lodash/lodash.h"
#include "lodash/types_check/is_map.h"

namespace lodash::test {

class IsMapTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(IsMapTest, is_map) {
    {
        auto res = types_check::is_map<std::map<int, int>>;
        EXPECT_TRUE(res);
    }

    {
        auto res = types_check::is_map<std::vector<int>>;
        EXPECT_FALSE(res);
    }
}

}  // namespace lodash::test
