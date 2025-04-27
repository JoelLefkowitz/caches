#ifndef CACHES_ABSTRACT_DEQUE_CACHE_TPP
#define CACHES_ABSTRACT_DEQUE_CACHE_TPP

#include "deque_cache.hpp"
#include <cstddef>
#include <deque>
#include <iterator>
#include <numeric>
#include <vector>

template <typename T>
caches::DequeCache<T>::DequeCache(size_t limit) : limit(limit)
                                                , cache({}) {
}

template <typename T>
typename std::deque<T>::iterator caches::DequeCache<T>::begin() {
    return cache.begin();
}

template <typename T>
typename std::deque<T>::iterator caches::DequeCache<T>::end() {
    return cache.end();
}

template <typename T>
typename std::deque<T>::const_iterator caches::DequeCache<T>::begin() const {
    return cache.begin();
}

template <typename T>
typename std::deque<T>::const_iterator caches::DequeCache<T>::end() const {
    return cache.end();
}

template <typename T>
size_t caches::DequeCache<T>::size() const {
    return cache.size();
}

template <typename T>
size_t caches::DequeCache<T>::space() const {
    auto current = size();
    return limit > current ? limit - current : 0;
}

template <typename T>
bool caches::DequeCache<T>::empty() const {
    return cache.empty();
}

template <typename T>
void caches::DequeCache<T>::clear() {
    cache.clear();
}

#endif
