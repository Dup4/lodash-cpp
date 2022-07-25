#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <map>
#include <vector>

#include "lodash/lodash.h"
#include "lodash/type_utility/get_result_type.h"

namespace lodash::type_utility::test {

class GetResultTypeTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(GetResultTypeTest, get_result_type) {
    {
        auto f = [](int& x) -> int {
            return x;
        };

        using t = get_result_type_t<std::vector<int>, decltype(f)>;
        auto res = std::is_same_v<t, int>;
        EXPECT_TRUE(res);
    }

    {
        auto f = [](int& x, [[maybe_unused]] const size_t& ix) {
            return x;
        };

        using t = get_result_type_t<std::vector<int>, decltype(f)>;
        auto res = std::is_same_v<t, int>;
        EXPECT_TRUE(res);
    }

    {
        auto f = []([[maybe_unused]] const std::string& key, int& x) {
            return x;
        };

        using t = get_result_type_t<std::map<std::string, int>, decltype(f)>;
        auto res = std::is_same_v<t, int>;
        EXPECT_TRUE(res);
    }
}

}  // namespace lodash::type_utility::test
