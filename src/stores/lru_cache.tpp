#ifndef CACHES_STORES_LRU_CACHE_TPP
#define CACHES_STORES_LRU_CACHE_TPP

#include "lru_cache.hpp"
#include <cstddef>
#include <deque>
#include <list>
#include <map>
#include <numeric>
#include <stdexcept>
#include <unordered_map>
#include <vector>

template <typename K, typename V>
caches::LRUCache<K, V>::LRUCache(size_t limit) : limit(limit) {}

template <typename K, typename V>
size_t caches::LRUCache<K, V>::size() const {
    return map.size();
}

template <typename K, typename V>
size_t caches::LRUCache<K, V>::space() const {
    auto current = size();
    return limit > current ? limit - current : 0;
}

template <typename K, typename V>
V caches::LRUCache<K, V>::operator[](const K &key) {
    auto it = map.find(key);

    if (it != map.end()) {
        list.splice(list.begin(), list, it->second);
        return it->second->second;
    }

    throw std::range_error("Missing key");
}

template <typename K, typename V>
bool caches::LRUCache<K, V>::contains(const K &key) const {
    return map.find(key) != map.end();
}

template <typename K, typename V>
void caches::LRUCache<K, V>::store(const K &key, const V &value) {
    auto it = map.find(key);
    list.push_front(std::pair<K, V>(key, value));

    if (it != map.end()) {
        list.erase(it->second);
        map.erase(it);
    }

    map[key] = list.begin();

    if (map.size() > limit) {
        auto last = list.end();
        last--;

        map.erase(last->first);
        list.pop_back();
    }
}

#endif
