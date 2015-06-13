#include "libdht/dht.hpp"
#include "gtest/gtest.h"

TEST(DHTTestCase, DHTTest)
{
    libdht::DHT dht;

    EXPECT_EQ(dht.print(), 1);
}
