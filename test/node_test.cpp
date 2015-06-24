#include "libdht/node.hpp"
#include "gtest/gtest.h"

TEST(NodeTestCase, NodeIDTest)
{
    libdht::Node node;

    EXPECT_EQ(node.id().data().size(), libdht::kIDSize);
}
