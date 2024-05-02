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

template <typename T>
caches::StoreCache<T>::StoreCache(size_t limit) : limit(limit) {}

template <typename T>
size_t caches::StoreCache<T>::size() const {
    return map.size();
}

template <typename T>
bool caches::StoreCache<T>::contains(const std::string &key) const {
    return map.find(key) != map.end();
}

template <typename T>
void caches::StoreCache<T>::store(const std::string &key, T &&value) {
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

template <typename T>
T &caches::StoreCache<T>::at(const std::string &key) {
    auto it = map.find(key);

    if (it != map.end()) {
        list.splice(list.begin(), list, it->second);
        return it->second->second;
    }

    throw std::range_error("Missing key");
}

#endif
