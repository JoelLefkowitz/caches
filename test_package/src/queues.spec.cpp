#include <caches/queues/fifo_cache.tpp>
#include <caches/queues/lifo_cache.tpp>
#include <cstddef>
#include <gtest/gtest.h>

TEST(FIFOCache, Caches) {
    caches::FIFOCache<int> cache(2);

    cache.push(1);
    cache.push(2);
    cache.push(3);

    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache.next(), 2);
    EXPECT_EQ(cache.last(), 3);
}

TEST(LIFOCache, Caches) {
    caches::LIFOCache<int> cache(2);

    cache.push(1);
    cache.push(2);
    cache.push(3);

    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache.next(), 3);
    EXPECT_EQ(cache.last(), 2);
}
