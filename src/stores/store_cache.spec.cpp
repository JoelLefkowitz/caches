#include "store_cache.tpp"
#include <gtest/gtest.h>
#include <string>

using namespace caches;

class Resource {
  public:
    size_t id;

    explicit Resource(size_t id) : id(id) {
    }

    Resource(const Resource &)            = delete;
    Resource &operator=(const Resource &) = delete;

    Resource(Resource &&resource) noexcept : id(resource.id) {
    }

    Resource &operator=(Resource &&) = delete;

    ~Resource() = default;
};

TEST(StoreCache, Store) {
    StoreCache<std::string, Resource> cache;

    cache.store("a", Resource(1));
    EXPECT_EQ(cache.at("a").id, 1);

    cache.store("b", Resource(2));
    EXPECT_EQ(cache.at("b").id, 2);
}

TEST(StoreCache, Limit) {
    StoreCache<std::string, Resource> cache(2);
    EXPECT_EQ(cache.size(), 0UL);
    EXPECT_EQ(cache.space(), 2UL);

    cache.store("a", Resource(1));
    EXPECT_EQ(cache.size(), 1UL);
    EXPECT_EQ(cache.space(), 1UL);

    cache.store("b", Resource(2));
    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache.space(), 0UL);

    cache.store("c", Resource(3));
    EXPECT_EQ(cache.size(), 2UL);
    EXPECT_EQ(cache.space(), 0UL);
}

TEST(StoreCache, Lru) {
    StoreCache<std::string, Resource> cache(2);

    cache.store("a", Resource(1));
    cache.store("b", Resource(2));

    cache.at("a");

    cache.store("c", Resource(3));

    EXPECT_TRUE(cache.contains("a"));
    EXPECT_TRUE(cache.contains("c"));

    EXPECT_FALSE(cache.contains("b"));
}

TEST(StoreCache, Clear) {
    StoreCache<std::string, Resource> cache(2);

    cache.store("a", Resource(1));
    EXPECT_EQ(cache.size(), 1UL);
    EXPECT_FALSE(cache.empty());

    cache.clear();
    EXPECT_EQ(cache.size(), 0UL);
    EXPECT_TRUE(cache.empty());
}
