# Caches

...

![Review](https://img.shields.io/github/actions/workflow/status/JoelLefkowitz/caches/review.yml)
![Quality](https://img.shields.io/codacy/grade/...)

## Installing

```bash
conan install caches
```

You can also download the [sources](https://download-directory.github.io?url=https://github.com/joellefkowitz/caches/tree/master/src).

## Documentation

Documentation and more detailed examples are hosted on [Github Pages](https://joellefkowitz.github.io/caches).

## Usage

...

### FIFOCache

![FIFOCache](docs/images/FIFOCache.png)

### LIFOCache

![LIFOCache](docs/images/LIFOCache.png)

### LRUCache

![LRUCache](docs/images/LRUCache.png)

### StoreCache

![StoreCache](docs/images/StoreCache.png)

## Tooling

...

pip - Python dependencies
yarn - JavaScript dependencies
conan - C++ dependencies and publisher
scons - C++ build system and task runner
husky - Git hooks
GitHub Actions - CI

Linters
cspell
cppclean
cppcheck
iwyu
trufflehog
clang-tidy

Formatters
prettier
clang-format

Contributing:
Issue, PR, Actions

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

// Handle .cpp sources
// Build and publish on windows
// Remap includes paths to be simpler
