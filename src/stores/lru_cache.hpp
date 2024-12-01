#ifndef CACHES_STORES_LRU_CACHE_HPP
#define CACHES_STORES_LRU_CACHE_HPP

#include <cstddef>
#include <deque>
#include <list>
#include <map>
#include <numeric>
#include <stdexcept>
#include <unordered_map>

namespace caches {
    template <typename K, typename V>
    using Pairs = typename std::list<std::pair<K, V>>::iterator;

    template <typename K, typename V>
    class LRUCache {
      private:
        size_t limit;

        std::list<std::pair<K, V>> list;

        std::unordered_map<K, Pairs<K, V>> map;

      public:
        explicit LRUCache(size_t limit = 100);

        V operator[](const K &key);

        size_t size() const;
        size_t space() const;

        bool contains(const K &key) const;

        void store(const K &key, const V &value);
    };
}

#endif
