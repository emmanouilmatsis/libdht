#include "libdht/id.hpp"
#include "gtest/gtest.h"

#include <iostream>

TEST(IDTestCase, DefaultConstructorTest)
{
    libdht::ID id;

    EXPECT_EQ(id.data().size(), libdht::kIDSize);
}

TEST(IDTestCase, StringConstructorTest)
{
    libdht::ID id("value");

    std::ostringstream os;
    os << id;

    EXPECT_EQ(os.str(), libdht::sha1("value"));
}

TEST(IDTestCase, PrefixTest)
{
    libdht::ID id_a("a"); // 86f7e437faa5a7fce15d1ddcb9eaeaea377667b8
    libdht::ID id_b("b"); // e9d71f5ee7c92d6dc9e92ffdad17b8bd49418f98

    EXPECT_EQ(static_cast<int>(id_a.prefix(id_b)), 1);
}

TEST(IDTestCase, RelationalOperatorsTest)
{
    libdht::ID id_a("a"); // 86f7e437faa5a7fce15d1ddcb9eaeaea377667b8
    libdht::ID id_b("b"); // e9d71f5ee7c92d6dc9e92ffdad17b8bd49418f98

    EXPECT_FALSE(id_a == id_b);
    EXPECT_TRUE(id_a != id_b);
    EXPECT_TRUE(id_a < id_b);
    EXPECT_FALSE(id_a > id_b);
    EXPECT_TRUE(id_a <= id_b);
    EXPECT_FALSE(id_a > id_b);
}
