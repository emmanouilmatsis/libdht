#include "libdht/sha1.hpp"
#include "gtest/gtest.h"

TEST(SHA1TestCase, HashTest)
{
    EXPECT_NE(libdht::sha1("grape"), std::string("grape"));
    EXPECT_EQ(libdht::sha1("grape"), std::string("bc8a2f8cdedb005b5c787692853709b060db75ff"));
}
