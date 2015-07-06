#include "libdht/id.hpp"
#include "gtest/gtest.h"

#include <iostream>

TEST(IDTestCase, DefaultConstructorTest)
{
    libdht::ID id;
}

TEST(IDTestCase, StringConstructorTest)
{
    libdht::ID id("value"); // f32b67c7e26342af42efabc674d441dca0a281c5

    EXPECT_EQ(std::bitset<libdht::kIDSize>(std::string("1111001100101011011001111100011111100010011000110100001010101111010000101110111110101011110001100111010011010100010000011101110010100000101000101000000111000101")), id.data());
}

TEST(IDTestCase, DataConstructorTest)
{
    libdht::ID id(std::bitset<libdht::kIDSize>().flip()); // ffffffffffffffffffffffffffffffffffffffff

    EXPECT_EQ(std::bitset<libdht::kIDSize>(std::string("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111")), id.data());
}

TEST(IDTestCase, PrefixTest)
{
    libdht::ID id_a("a"); // 86f7e437faa5a7fce15d1ddcb9eaeaea377667b8
    libdht::ID id_b("b"); // e9d71f5ee7c92d6dc9e92ffdad17b8bd49418f98
    libdht::ID id_c("-"); // 3bc15c8aae3e4124dd409035f32ea2fd6835efc9

    EXPECT_EQ(0, id_a.prefix(id_c));
    EXPECT_EQ(1, id_a.prefix(id_b));
    EXPECT_EQ(160, id_a.prefix(id_a));
}

TEST(IDTestCase, RelationalOperatorsTest)
{
    libdht::ID id_a("a"); // 86f7e437faa5a7fce15d1ddcb9eaeaea377667b8
    libdht::ID id_b("b"); // e9d71f5ee7c92d6dc9e92ffdad17b8bd49418f98

    EXPECT_TRUE(id_a == id_a);
    EXPECT_FALSE(id_a == id_b);
    EXPECT_TRUE(id_a != id_b);
    EXPECT_TRUE(id_a < id_b);
    EXPECT_FALSE(id_a > id_b);
    EXPECT_TRUE(id_a <= id_b);
    EXPECT_FALSE(id_a >= id_b);
}
