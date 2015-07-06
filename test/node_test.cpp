#include "libdht/node.hpp"
#include "gtest/gtest.h"

TEST(NodeTestCase, DefaultConstructorTest)
{
    libdht::Node node;

    EXPECT_EQ("0.0.0.0", node.address());
    EXPECT_EQ(1337, node.port());
}

TEST(NodeTestCase, IDAddressPortConstructorTest)
{
    libdht::ID id;
    std::string address("0.0.0.0");
    int port = 1337;

    libdht::Node node(id, address, port);

    EXPECT_EQ(id, node.id());
    EXPECT_EQ(address, node.address());
    EXPECT_EQ(port, node.port());
}
