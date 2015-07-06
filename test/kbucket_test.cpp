#include "libdht/kbucket.hpp"
#include "gtest/gtest.h"

TEST(KBucketTestCase, DefaultConstructorTest)
{
    libdht::KBucket kbucket;

    EXPECT_TRUE(kbucket.prefix().none());
}

TEST(KBucketTestCase, RangeConstructorTest)
{
    std::bitset<libdht::kIDSize> prefix;
    prefix.flip();

    libdht::KBucket kbucket(prefix);

    EXPECT_TRUE(kbucket.prefix().all());
}

TEST(KBucketTestCase, AddTest)
{
    libdht::Node node;

    libdht::KBucket kbucket;

    kbucket.add(node);

    EXPECT_EQ(1, std::distance(kbucket.begin(), kbucket.end()));
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

    libdht::KBucket kbucket_b(std::bitset<libdht::kIDSize>().flip());

    EXPECT_FALSE(kbucket_b.covers(node));
}

TEST(KBucketTestCase, DepthTest)
{
    libdht::KBucket kbucket;

    for (auto i = 0; i < libdht::kK; i++)
    {
        auto data = libdht::ID().data().reset(libdht::kIDSize - 1);
        kbucket.add(libdht::Node(libdht::ID(data), "", 0));
    }

    EXPECT_GE(kbucket.depth(), 1);
}
