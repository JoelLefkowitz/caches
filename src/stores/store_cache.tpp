#ifndef CACHES_STORES_STORE_CACHE_TPP
#define CACHES_STORES_STORE_CACHE_TPP

#include "store_cache.hpp"
#include <cstddef>
#include <deque>
#include <list>
#include <map>
#include <numeric>
#include <stdexcept>
#include <unordered_map>
#include <vector>

template <typename K, typename V>
caches::StoreCache<K, V>::StoreCache(size_t limit) : limit(limit) {
}

template <typename K, typename V>
size_t caches::StoreCache<K, V>::size() const {
    return map.size();
}

template <typename K, typename V>
size_t caches::StoreCache<K, V>::space() const {
    auto current = size();
    return limit > current ? limit - current : 0;
}

template <typename K, typename V>
V &caches::StoreCache<K, V>::at(const K &key) {
    auto it = map.find(key);

    if (it != map.end()) {
        list.splice(list.begin(), list, it->second);
        return it->second->second;
    }

    throw std::range_error("Missing key");
}

template <typename K, typename V>
bool caches::StoreCache<K, V>::contains(const K &key) const {
    return map.find(key) != map.end();
}

template <typename K, typename V>
void caches::StoreCache<K, V>::store(const K &key, V &&value) {
    auto it = map.find(key);

    list.push_front(std::make_pair(key, std::move(value)));

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
