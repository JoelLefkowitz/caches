#ifndef CACHES_ABSTRACT_DEQUE_CACHE_HPP
#define CACHES_ABSTRACT_DEQUE_CACHE_HPP

#include <cstddef>
#include <deque>
#include <iterator>
#include <numeric>
#include <vector>

namespace caches {
    template <typename T>
    class DequeCache {
      protected:
        size_t limit = 0;

        std::deque<T> cache;

      public:
        explicit DequeCache(size_t limit = 100);

        virtual ~DequeCache() = default;

        virtual T next() const = 0;
        virtual T last() const = 0;

        virtual void push(T value) = 0;
        virtual void pop()         = 0;

        virtual std::vector<T> slice(size_t width) const = 0;

        typename std::deque<T>::iterator begin();
        typename std::deque<T>::iterator end();

        typename std::deque<T>::const_iterator begin() const;
        typename std::deque<T>::const_iterator end() const;

        size_t size() const;
        size_t space() const;

        bool empty() const;
    };
}

#endif
