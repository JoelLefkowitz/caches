#include "fifo_cache.tpp"
#include <cstddef>
#include <gtest/gtest.h>

using namespace caches;

TEST(FIFOCache, Fill) {
    FIFOCache<int> cache(3);
    EXPECT_EQ(cache.size(), 0UL);
    EXPECT_EQ(cache.space(), 3UL);

    cache.push(1);
    EXPECT_EQ(cache.size(), 1UL);
    EXPECT_EQ(cache.space(), 2UL);
    EXPECT_EQ(cache.next(), 1);
    EXPECT_EQ(cache.last(), 1);

    cache.push(2);
    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache.space(), 1UL);
    EXPECT_EQ(cache.next(), 1);
    EXPECT_EQ(cache.last(), 2);

    cache.push(3);
    EXPECT_EQ(cache.size(), 3UL);
    EXPECT_EQ(cache.space(), 0UL);
    EXPECT_EQ(cache.next(), 1);
    EXPECT_EQ(cache.last(), 3);

    cache.push(4);
    EXPECT_EQ(cache.size(), 3UL);
    EXPECT_EQ(cache.space(), 0UL);
    EXPECT_EQ(cache.next(), 2);
    EXPECT_EQ(cache.last(), 4);
}

TEST(FIFOCache, Pop) {
    FIFOCache<int> cache(3);

    cache.push(1);
    cache.push(2);
    cache.push(3);
    cache.pop();

    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache.next(), 2);
    EXPECT_EQ(cache.last(), 3);
}

TEST(FIFOCache, Slice) {
    FIFOCache<int> cache(3);

    cache.push(1);
    cache.push(2);
    cache.push(3);

    EXPECT_EQ(cache.slice(1), std::vector<int>({3}));
    EXPECT_EQ(cache.slice(2), std::vector<int>({2, 3}));
    EXPECT_EQ(cache.slice(3), std::vector<int>({1, 2, 3}));
    EXPECT_EQ(cache.slice(10), std::vector<int>({1, 2, 3}));
}

TEST(FIFOCache, Clear) {
    FIFOCache<int> cache(3);

    cache.push(1);
    EXPECT_EQ(cache.size(), 1UL);
    EXPECT_FALSE(cache.empty());

    cache.clear();
    EXPECT_EQ(cache.size(), 0UL);
    EXPECT_TRUE(cache.empty());
}
