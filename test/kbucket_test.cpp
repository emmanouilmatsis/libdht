#include "libdht/kbucket.hpp"
#include "gtest/gtest.h"

TEST(KBucketTestCase, DefaultConstructorTest)
{
    libdht::KBucket kbucket;
}

TEST(KBucketTestCase, RangeConstructorTest)
{
    std::array<uint8_t, libdht::kIDSize> min;
    min.fill(static_cast<uint8_t>(0));

    std::array<uint8_t, libdht::kIDSize> max;
    max.fill(static_cast<uint8_t>(255));

    libdht::KBucket kbucket(std::make_pair(min, max));
}

TEST(KBucketTestCase, AddTest)
{
    libdht::Node node;

    libdht::KBucket kbucket;

    kbucket.add(node);
}

TEST(KBucketTestCase, ContainsTest)
{
    libdht::Node node;

    libdht::KBucket kbucket;

    kbucket.add(node);

    EXPECT_TRUE(kbucket.contains(node));
}

TEST(KBucketTestCase, FullTest)
{
    libdht::KBucket kbucket;

    for (int i = 0; i < libdht::kK; i++)
        kbucket.add(libdht::Node());

    EXPECT_TRUE(kbucket.full());
}

TEST(KBucketTestCase, CoversTest)
{
    libdht::Node node;

    libdht::KBucket kbucket_a;

    EXPECT_TRUE(kbucket_a.covers(node));

    std::array<uint8_t, libdht::kIDSize> min;
    min.fill(static_cast<uint8_t>(0));
    std::array<uint8_t, libdht::kIDSize> max;
    max.fill(static_cast<uint8_t>(0));

    libdht::KBucket kbucket_b(std::make_pair(min, max));

    EXPECT_FALSE(kbucket_b.covers(node));
}

TEST(KBucketTestCase, DepthTest)
{
    libdht::KBucket kbucket;

    for (auto i = 0; i < libdht::kK; i++)
    {
        auto data = libdht::ID().data();
        data.front() = static_cast<uint8_t>(0);

        kbucket.add(libdht::Node(libdht::ID(data)));
    }

    EXPECT_GE(kbucket.depth(), 8);
}
