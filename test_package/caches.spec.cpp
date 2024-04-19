#include <caches/queues/fifo_cache.tpp>
#include <caches/queues/lifo_cache.tpp>
#include <caches/stores/lru_cache.tpp>
#include <caches/stores/store_cache.tpp>
#include <cstddef>
#include <gtest/gtest.h>

using namespace caches;

TEST(FIFOCache, Caches) {
    FIFOCache<int> cache(2);

    cache.push(1);
    cache.push(2);
    cache.push(3);

    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache.next(), 2);
    EXPECT_EQ(cache.last(), 3);
}

TEST(LIFOCache, Caches) {
    LIFOCache<int> cache(2);

    cache.push(1);
    cache.push(2);
    cache.push(3);

    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache.next(), 3);
    EXPECT_EQ(cache.last(), 2);
}

TEST(LRUCache, Caches) {
    LRUCache<std::string, int> cache(2);

    cache.store("a", 1);
    cache.store("b", 2);
    cache.store("c", 3);

    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache["b"], 2);
    EXPECT_EQ(cache["c"], 3);
}

TEST(StoreCache, Caches) {
    StoreCache<int> cache(2);

    cache.store("a", 1);
    cache.store("b", 2);
    cache.store("c", 3);

    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache.at("b"), 2);
    EXPECT_EQ(cache.at("c"), 3);
}
