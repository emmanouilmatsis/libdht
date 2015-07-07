#include "libdht/node.hpp"
#include "gtest/gtest.h"

TEST(NodeTestCase, DefaultConstructorTest)
{
    libdht::Node node;

    EXPECT_EQ(libdht::kAddress, node.address());
    EXPECT_EQ(libdht::kPort, node.port());
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
