#ifndef CACHES_STORES_STORE_CACHE_HPP
#define CACHES_STORES_STORE_CACHE_HPP

#include <cstddef>
#include <deque>
#include <functional>
#include <list>
#include <map>
#include <numeric>
#include <stdexcept>
#include <string>
#include <unordered_map>

// cppclean-disable-next-line
#include "../abstract/aliases.hpp"

namespace caches {
    template <typename K, typename V>
    class StoreCache {
      protected:
        size_t limit;

        std::list<std::pair<K, V>> list;

        std::unordered_map<K, Pairs<K, V>> map;

      public:
        explicit StoreCache(size_t limit = 100);

        size_t size() const;
        size_t space() const;

        V &at(const K &key);

        bool contains(const K &key) const;

        void store(const K &key, V &&value);
    };
}

#endif
