#ifndef LIFO_CACHE_HPP
#define LIFO_CACHE_HPP

#include "deque_cache.hpp"
#include <cstddef>
#include <deque>
#include <numeric>
#include <vector>

namespace caches {
    template <typename T>
    class LIFOCache : public DequeCache<T> {
      public:
        explicit LIFOCache(size_t limit = 100);

        T next() const override;
        T last() const override;

        void push(T value) override;
        void pop() override;

        std::vector<T> slice(size_t width) const override;
    };
}

#endif
