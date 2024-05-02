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
#include "lru_cache.hpp"

namespace caches {
    template <typename T>
    class StoreCache {
      protected:
        size_t limit;

        std::list<std::pair<std::string, T>> list;

        std::unordered_map<std::string, Pairs<std::string, T>> map;

      public:
        explicit StoreCache(size_t limit = 100);

        size_t size() const;

        bool contains(const std::string &key) const;

        void store(const std::string &key, T &&value);

        T &at(const std::string &key);
    };
}

#endif
