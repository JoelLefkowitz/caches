#include <caches/stores/lru_cache.tpp>
#include <caches/stores/store_cache.tpp>
#include <cstddef>
#include <gtest/gtest.h>

using namespace caches;

TEST(LRUCache, Caches) {
    caches::LRUCache<std::string, int> cache(2);

    cache.store("a", 1);
    cache.store("b", 2);
    cache.store("c", 3);

    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache["b"], 2);
    EXPECT_EQ(cache["c"], 3);
}

TEST(StoreCache, Caches) {
    caches::StoreCache<int> cache(2);

    cache.store("a", 1);
    cache.store("b", 2);
    cache.store("c", 3);

    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache.at("b"), 2);
    EXPECT_EQ(cache.at("c"), 3);
}
