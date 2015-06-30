#include "libdht/routing_table.hpp"
#include "gtest/gtest.h"

#include "libdht/constants.hpp"

TEST(RoutingTableTestCase, DefaultConstructorTest)
{
    auto routing_table = libdht::RoutingTable();
    auto kbucket = *routing_table.begin();

    std::array<uint8_t, libdht::kIDSize> min;
    std::array<uint8_t, libdht::kIDSize> max;

    min.fill(static_cast<uint8_t>(0));
    max.fill(static_cast<uint8_t>(255));

    EXPECT_EQ(std::make_pair(libdht::ID(min), libdht::ID(max)), kbucket.range());

    min.fill(static_cast<uint8_t>(1));
    max.fill(static_cast<uint8_t>(254));

    EXPECT_NE(std::make_pair(libdht::ID(min), libdht::ID(max)), kbucket.range());
}

TEST(RoutingTableTestCase, AddContactTest)
{
    auto routing_table = libdht::RoutingTable();

    EXPECT_EQ(1, std::distance(routing_table.begin(), routing_table.end()));

    for (int i = 0; i <= libdht::kK; i++)
    {
        std::array<uint8_t, libdht::kIDSize> data;
        data.fill(static_cast<uint8_t>(i));

        routing_table.add_contact(libdht::Node(data));
    }

    std::cout << "======================================================" << std::endl;
    for (const auto &kbucket : routing_table)
    {
        std::cout << "kbucket: ";
        std::cout << "[" << kbucket.range().first;
        std::cout << "," << kbucket.range().second;
        std::cout << "]" << std::endl << std::endl;
    }

    EXPECT_EQ(5, std::distance(routing_table.begin(), routing_table.end()));
}
