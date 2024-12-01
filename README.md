# Caches

Extensible cache templates.

c++11
dependency free
header only

![Review](https://img.shields.io/github/actions/workflow/status/JoelLefkowitz/caches/review.yml)
![Quality](https://img.shields.io/codacy/grade/980b16173dc7422bbd4b67a79e2e985b)

## Motivation

Consider the following scenario:

- You need to generate textures for a game renderer
- The textures can be given unique names so they can be reused
- Eventually each texture won't be needed when the game scene moves on

You need to store the textures in a `map` but you need to remove the oldest textures when adding new ones to limit the container size.

This is a sufficiently frequent scenario for a generic template: `caches::StoreCache` tracks the least recently used key and allows access by reference:

```cpp
#include <string>
#include <caches/stores/store_cache.tpp>

class Texture() { ... }

caches::StoreCache<Texture> cache(2);

Texture texture_a;
cache.store("a", texture_a);

Texture texture_b;
cache.store("b", texture_b);

Texture texture_c;

// This pops texture_a
cache.store("c", texture_c);

cache.size() -> 2UL
cache.at("b") -> texture_b
cache.at("c") -> texture_c
```

## Installing

```bash
conan search caches
```

You can also download the [sources](https://download-directory.github.io?url=https://github.com/JoelLefkowitz/caches/tree/master/src).

## Documentation

Documentation and more detailed examples are hosted on [Github Pages](https://joellefkowitz.github.io/caches).

## Usage

### FIFOCache

- First in, first out
- Fixed size cache with generic `T` elements
- Access by value with `T next() const` and `T last() const`

<div align='center'>
    <img width=300 height=400 src='docs/images/FIFOCache.png'alt='FIFOCache' />
</div >

```cpp
#include <string>
#include <caches/queues/fifo_cache.tpp>

caches::FIFOCache<std::string> cache(2);

First in, first out, with a fixed size:

cache.push("a");
cache.push("b");
cache.push("c");

cache.size() -> 2UL
cache.next() -> "b"
cache.last() -> "c"
```

### LIFOCache

- Last in, first out
- Fixed size cache with generic `T` elements
- Access by value with `T next() const` and `T last() const`

<div align='center'>
    <img width=300 height=400 src='docs/images/LIFOCache.png'alt='LIFOCache' />
</div >

```cpp
#include <string>
#include <caches/queues/lifo_cache.tpp>

caches::LIFOCache<std::string> cache(2);

cache.push("a");
cache.push("b");
cache.push("c");

cache.size() -> 2UL
cache.next() -> "c"
cache.last() -> "b"
```

### LRUCache

- Pops the least recently accessed key
- Fixed size cache of generic `K: V` pairs
- Access by value with `operator[](const K &key)`

<div align='center'>
    <img width=300 height=400 src='docs/images/LRUCache.png'alt='LRUCache' />
</div >

```cpp
#include <string>
#include <caches/stores/lru_cache.tpp>

caches::LRUCache<std::string, int> cache(2);

cache.store("a", 1);
cache.store("b", 2);
cache.store("c", 3);

cache.size() -> 2UL
cache["b"] ->  2
cache["c"] ->  3
```

### StoreCache

- Pops the least recently accessed key
- Fixed size cache of `string: T` pairs
- Access by reference with `T &at(const std::string &key)`

<div align='center'>
    <img width=300 height=400 src='docs/images/StoreCache.png'alt='StoreCache' />
</div >

```cpp
#include <string>
#include <caches/stores/store_cache.tpp>

caches::StoreCache<int> cache(2);

cache.store("a", 1);
cache.store("b", 2);
cache.store("c", 3);

cache.size() -> 2UL
cache.at("b") -> 2
cache.at("c") -> 3
```

## Tooling

### Dependencies

To install dependencies:

```bash
yarn install
pip install .[all]
conan install .
```

### Tests

To run tests:

```bash
scons test
```

### Documentation

To generate the documentation locally:

```bash
scons docs
```

### Linters

To run linters:

```bash
scons lint
```

### Formatters

To run formatters:

```bash
scons format
```

## Contributing

Please read this repository's [Code of Conduct](CODE_OF_CONDUCT.md) which outlines our collaboration standards and the [Changelog](CHANGELOG.md) for details on breaking changes that have been made.

This repository adheres to semantic versioning standards. For more information on semantic versioning visit [SemVer](https://semver.org).

Bump2version is used to version and tag changes. For example:

```bash
bump2version patch
```

### Contributors

- [Joel Lefkowitz](https://github.com/joellefkowitz) - Initial work

## Remarks

Lots of love to the open source community!

<div align='center'>
    <img width=200 height=200 src='https://media.giphy.com/media/osAcIGTSyeovPq6Xph/giphy.gif' alt='Be kind to your mind' />
    <img width=200 height=200 src='https://media.giphy.com/media/KEAAbQ5clGWJwuJuZB/giphy.gif' alt='Love each other' />
    <img width=200 height=200 src='https://media.giphy.com/media/WRWykrFkxJA6JJuTvc/giphy.gif' alt="It's ok to have a bad day" />
</div>
