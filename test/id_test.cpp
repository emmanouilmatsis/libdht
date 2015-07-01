#include "libdht/id.hpp"
#include "gtest/gtest.h"

#include <iostream>

TEST(IDTestCase, DefaultConstructorTest)
{
    libdht::ID id_a;
    libdht::ID id_b;

    EXPECT_NE(id_a.data(), id_b.data());
}

TEST(IDTestCase, StringConstructorTest)
{
    libdht::ID id("value");

    std::ostringstream os;
    os << id;

    EXPECT_EQ(os.str(), libdht::sha1("value"));
}

TEST(IDTestCase, DataConstructorTest)
{
    /*
    std::bitset<kIDSize> data;
    data.flip();
    libdht::ID id(data);
    */
    libdht::ID id(std::bitset<kIDSize>().flip());

    std::ostringstream os;
    os << id;

    EXPECT_EQ(os.str(), "ffffffffffffffffffffffffffffffffffffffff");
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
