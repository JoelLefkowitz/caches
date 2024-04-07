#include "store_cache.tpp"
#include <gtest/gtest.h>

using namespace caches;

class TestResource {
  public:
    std::string str;

    explicit TestResource(const std::string &str) : str(str) {}

    TestResource(const TestResource &)            = delete;
    TestResource &operator=(const TestResource &) = delete;

    TestResource(TestResource &&resource) noexcept : str(resource.str) {}

    TestResource &operator=(TestResource &&) = delete;

    ~TestResource() = default;

    bool operator==(const TestResource &rhs) const { return str == rhs.str; }
};

TEST(StoreCache, Limit) {
    StoreCache<TestResource> store(2);

    store.store("a", TestResource("a"));
    store.store("b", TestResource("b"));
    store.store("c", TestResource("c"));

    EXPECT_TRUE(store.contains("b"));
    EXPECT_TRUE(store.contains("c"));

    EXPECT_FALSE(store.contains("a"));

    EXPECT_EQ(store.at("b").str, "b");
    EXPECT_EQ(store.at("c").str, "c");
}

TEST(StoreCache, Lru) {
    StoreCache<TestResource> store(2);

    store.store("a", TestResource("a"));
    store.store("b", TestResource("b"));

    store.at("a");

    store.store("c", TestResource("c"));

    EXPECT_TRUE(store.contains("a"));
    EXPECT_TRUE(store.contains("c"));
    
    EXPECT_FALSE(store.contains("b"));

    EXPECT_EQ(store.at("a").str, "a");
    EXPECT_EQ(store.at("c").str, "c");
}
