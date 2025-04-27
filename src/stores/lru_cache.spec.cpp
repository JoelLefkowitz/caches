#include "lru_cache.tpp"
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
    LRUCache<std::string, int> cache(2);
    EXPECT_EQ(cache.size(), 0UL);
    EXPECT_EQ(cache.space(), 2UL);

    cache.store("a", 1);
    EXPECT_EQ(cache.size(), 1UL);
    EXPECT_EQ(cache.space(), 1UL);

    cache.store("b", 2);
    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache.space(), 0UL);

    cache.store("c", 3);
    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache.space(), 0UL);
}

TEST(LRUCache, Lru) {
    LRUCache<std::string, int> cache(2);

    cache.store("a", 1);
    cache.store("b", 2);

    cache["a"];

    cache.store("c", 3);

    EXPECT_TRUE(cache.contains("a"));
    EXPECT_TRUE(cache.contains("c"));

    EXPECT_FALSE(cache.contains("b"));
}

TEST(LRUCache, Clear) {
    LRUCache<std::string, int> cache(2);

    cache.store("a", 1);
    EXPECT_EQ(cache.size(), 1UL);
    EXPECT_FALSE(cache.empty());

    cache.clear();
    EXPECT_EQ(cache.size(), 0UL);
    EXPECT_TRUE(cache.empty());
}
