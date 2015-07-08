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

    for (int i = 0; i < libdht::kK; i++)
        routing_table.add_contact(libdht::Node(libdht::ID(std::bitset<libdht::kIDSize>(i)), "", 0));

    EXPECT_FALSE(routing_table.add_contact(libdht::Node(libdht::ID(std::bitset<libdht::kIDSize>(libdht::kK)), "", 0)));

    EXPECT_GE(std::distance(routing_table.begin(), routing_table.end()), 6);
}
