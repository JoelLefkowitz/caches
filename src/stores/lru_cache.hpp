#ifndef CACHES_STORES_LRU_CACHE_HPP
#define CACHES_STORES_LRU_CACHE_HPP

#include <cstddef>
#include <deque>
#include <list>
#include <map>
#include <numeric>
#include <stdexcept>
#include <unordered_map>

// cppclean-disable-next-line
#include "../abstract/aliases.hpp"

namespace caches {
    template <typename K, typename V>
    class LRUCache {
      private:
        size_t limit;

        std::list<std::pair<K, V>> list;

        std::unordered_map<K, Pairs<K, V>> map;

      public:
        explicit LRUCache(size_t limit = 100);

        size_t size() const;
        size_t space() const;

        V operator[](const K &key);

        bool contains(const K &key) const;

        void store(const K &key, const V &value);

        bool empty() const;

        void clear();
    };
}

#endif
