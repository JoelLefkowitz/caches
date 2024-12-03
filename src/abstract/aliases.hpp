#ifndef CACHES_ABSTRACT_ALIASES_HPP
#define CACHES_ABSTRACT_ALIASES_HPP

#include <list>
#include <numeric>

namespace caches {
    template <typename K, typename V>
    using Pairs = typename std::list<std::pair<K, V>>::iterator;
}

#endif
