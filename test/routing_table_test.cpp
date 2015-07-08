#include "libdht/routing_table.hpp"
#include "gtest/gtest.h"

#include "libdht/constants.hpp"

TEST(RoutingTableTestCase, DefaultConstructorTest)
{
    auto routing_table = libdht::RoutingTable();
    auto kbucket = *routing_table.begin();

    EXPECT_EQ(0, kbucket.position().size());
}

TEST(RoutingTableTestCase, AddContactTest)
{
    auto routing_table = libdht::RoutingTable();

    EXPECT_EQ(1, std::distance(routing_table.begin(), routing_table.end()));

    for (int i = 0; i <= libdht::kK; i++)
    {
        std::bitset<libdht::kIDSize> data(i);
        routing_table.add_contact(libdht::Node(libdht::ID(data), "", 0));
    }

    EXPECT_GE(std::distance(routing_table.begin(), routing_table.end()), 6);
}
