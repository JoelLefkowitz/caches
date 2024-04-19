#ifndef LIFO_CACHE_TPP
#define LIFO_CACHE_TPP

#include "../abstract/deque_cache.tpp"
#include "lifo_cache.hpp"
#include <cstddef>
#include <deque>
#include <numeric>
#include <vector>

template <typename T>
caches::LIFOCache<T>::LIFOCache(size_t limit) : DequeCache<T>(limit) {}

template <typename T>
T caches::LIFOCache<T>::next() const {
    return this->cache.back();
}

template <typename T>
T caches::LIFOCache<T>::last() const {
    return this->cache.front();
}

template <typename T>
void caches::LIFOCache<T>::push(T value) {
    this->cache.push_back(value);

    if (this->cache.size() > this->limit) {
        this->cache.pop_front();
    }
}

template <typename T>
void caches::LIFOCache<T>::pop() {
    if (!this->cache.empty()) {
        this->cache.pop_back();
    }
}

template <typename T>
std::vector<T> caches::LIFOCache<T>::slice(size_t width) const {
    std::vector<T> samples;

    if (this->cache.size() > 0) {
        auto i = this->cache.begin();

        std::advance(i, this->cache.size() > width ? this->cache.size() - width : 0);

        for (; i != this->cache.end(); ++i) {
            samples.push_back(*i);
        }
    }

    return samples;
}

#endif
