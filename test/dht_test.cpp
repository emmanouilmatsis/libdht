#include "libdht/dht.hpp"
#include "gtest/gtest.h"

TEST(DHTTestCase, PrintOneTest)
{
    libdht::DHT dht;

    EXPECT_EQ(dht.print(), 1);
}
