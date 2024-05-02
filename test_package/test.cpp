#include <caches/stores/store_cache.tpp>
#include <cstddef>
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
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
