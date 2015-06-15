#include <iostream>
#include <random>

#include "gtest/gtest.h"

TEST(GenericTestCase, RandomTest)
{
    std::random_device rd;

    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> uniform_dist(1, 10);

    uniform_dist(mt);
}

TEST(GenericTestCase, StrToHexTest)
{
}
