#include "gtest/gtest.h"
#include "snapshot/snapshot.h"

#include <map>
#include <string>
#include <vector>

#include "lodash/lodash.h"

namespace lodash::test {

class TypeManipulationTest : public testing::Test {
protected:
    virtual void SetUp() override {}
};

TEST_F(TypeManipulationTest, empty) {
    EXPECT_EQ(Empty<int>(), 0);
    EXPECT_EQ(Empty<std::string>(), "");
}

}  // namespace lodash::test
