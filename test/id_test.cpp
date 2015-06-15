#include "libdht/id.hpp"
#include "gtest/gtest.h"

#include <iostream>

TEST(IDTestCase, DefaultConstructorTest)
{
    libdht::ID id;

    EXPECT_EQ(id.data().size(), libdht::HASH_LENGTH);
}

TEST(IDTestCase, StringConstructorTest)
{
    libdht::ID id("value");

    std::ostringstream os;
    os << id;

    EXPECT_EQ(os.str(), libdht::sha1("value"));
}
