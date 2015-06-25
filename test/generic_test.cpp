#include <iostream>
#include <array>
#include <algorithm>

#include "gtest/gtest.h"

TEST(GenericTestCase, GenericTest)
{
    constexpr int size = 10;

    std::array<int, size> arr;
    arr.fill(255);

    std::for_each(arr.begin(), arr.end(),
            [](const int &a) -> void {
                //std::cout << a << std::endl;
            });
}
