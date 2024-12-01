#include "store_cache.tpp"
#include <gtest/gtest.h>

using namespace caches;

class TestResource {
  public:
    std::string str;

    explicit TestResource(std::string str) : str(std::move(str)) {}

    TestResource(const TestResource &)            = delete;
    TestResource &operator=(const TestResource &) = delete;

    TestResource(TestResource &&resource) noexcept : str(std::move(resource.str)) {}

    TestResource &operator=(TestResource &&) = delete;

    ~TestResource() = default;

    bool operator==(const TestResource &rhs) const { return str == rhs.str; }
};

TEST(StoreCache, Store) {
    StoreCache<TestResource> cache;

    cache.store("a", TestResource("a"));
    EXPECT_EQ(cache.at("a").str, "a");

    cache.store("b", TestResource("b"));
    EXPECT_EQ(cache.at("b").str, "b");
}

TEST(StoreCache, Limit) {
    StoreCache<TestResource> cache(2);
    EXPECT_EQ(cache.size(), 0UL);
    EXPECT_EQ(cache.space(), 2UL);

    cache.store("a", TestResource("a"));
    EXPECT_EQ(cache.size(), 1UL);
    EXPECT_EQ(cache.space(), 1UL);

    cache.store("b", TestResource("b"));
    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache.space(), 0UL);

    cache.store("c", TestResource("c"));
    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache.space(), 0UL);
}

TEST(StoreCache, Lru) {
    StoreCache<TestResource> cache(2);

    cache.store("a", TestResource("a"));
    cache.store("b", TestResource("b"));

    cache.at("a");

    cache.store("c", TestResource("c"));

    EXPECT_TRUE(cache.contains("a"));
    EXPECT_TRUE(cache.contains("c"));

    EXPECT_FALSE(cache.contains("b"));
}
