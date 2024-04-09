#include "../include/lru_cache.tpp"
#include <gtest/gtest.h>
#include <string>

using namespace caches;

TEST(LRUCache, Store) {
    LRUCache<std::string, int> cache;

    cache.store("a", 1);
    EXPECT_EQ(cache["a"], 1);

    cache.store("a", 2);
    EXPECT_EQ(cache["a"], 2);
}

TEST(LRUCache, Limit) {
    LRUCache<std::string, int> cache(1);

    cache.store("a", 1);
    cache.store("b", 2);

    EXPECT_FALSE(cache.contains("a"));
    EXPECT_TRUE(cache.contains("b"));
}

TEST(LRUCache, Lru) {
    LRUCache<std::string, int> cache(2);

    cache.store("a", 1);
    cache.store("b", 2);

    cache["a"];

    cache.store("c", 3);

    EXPECT_TRUE(cache.contains("a"));
    EXPECT_FALSE(cache.contains("b"));
    EXPECT_TRUE(cache.contains("c"));
}
