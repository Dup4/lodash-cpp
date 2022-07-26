#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <map>
#include <vector>

#include "lodash/lodash.h"
#include "lodash/type_utility/get_result_type.h"

namespace lodash::type_utility::test {

class GetFlattenContainerValueTypeTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(GetFlattenContainerValueTypeTest, get_flatten_container_value_type) {
    {
        using t = get_flatten_container_value_type_t<std::vector<int>>;
        auto res = std::is_same_v<t, int>;
        EXPECT_TRUE(res);
    }

    {
        using t = get_flatten_container_value_type_t<std::map<int, int>>;
        auto res = std::is_same_v<t, std::pair<const int, int>>;
        EXPECT_TRUE(res);
    }

    {
        using t = get_flatten_container_value_type_t<std::vector<std::vector<int>>>;
        auto res = std::is_same_v<t, int>;
        EXPECT_TRUE(res);
    }
}

}  // namespace lodash::type_utility::test
