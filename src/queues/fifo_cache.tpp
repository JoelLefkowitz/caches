#ifndef FIFO_CACHE_TPP
#define FIFO_CACHE_TPP

#include "../abstract/deque_cache.tpp"
#include "fifo_cache.hpp"
#include <cstddef>
#include <deque>
#include <numeric>
#include <vector>

template <typename T>
caches::FIFOCache<T>::FIFOCache(size_t limit) : DequeCache<T>(limit) {}

template <typename T>
T caches::FIFOCache<T>::next() const {
    return this->cache.front();
}

template <typename T>
T caches::FIFOCache<T>::last() const {
    return this->cache.back();
}

template <typename T>
void caches::FIFOCache<T>::push(T value) {
    this->cache.push_back(value);

    if (this->cache.size() > this->limit) {
        this->cache.pop_front();
    }
}

template <typename T>
void caches::FIFOCache<T>::pop() {
    if (!this->cache.empty()) {
        this->cache.pop_front();
    }
}

template <typename T>
std::vector<T> caches::FIFOCache<T>::slice(size_t width) const {
    std::vector<T> samples;

    if (this->cache.size() > 0) {
        auto i = this->cache.cbegin();

        std::advance(i, this->cache.size() > width ? this->cache.size() - width : 0);

        for (; i != this->cache.cend(); ++i) {
            samples.push_back(*i);
        }
    }

    return samples;
}

#endif
