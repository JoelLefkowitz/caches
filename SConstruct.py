from miniscons import (
    Build,
    Flag,
    Routine,
    Script,
    Target,
    Tasks,
    conan,
    packages,
    flags,
)
from walkmate import tree

env = conan()

tests = Build(
    "tests",
    tree("src", r"\.cpp$", ["main.cpp"]),
    flags("c++11"),
    packages(["gtest"]),
)

includes = tests.packages["CPPPATH"]

clang_format = Script(
    "clang-format",
    ["-i", tree(".", r"\.(cpp|hpp|tpp)$")],
)

clang_tidy = Script(
    "clang-tidy",
    [
        tree("src", r"\.(cpp)$"),
        "--",
        [f"-I{i}" for i in includes],
    ],
)

cppclean = Script(
    "cppclean",
    ["."],
)

cppcheck = Script(
    "cppcheck",
    [
        tree("src", r"\.(cpp)$"),
        [f"-I{i}" for i in includes],
        [f"--suppress=*:{i}/*" for i in includes],
        "--quiet",
        "--enable=all",
        "--inline-suppr",
        "--suppressions-list=.cppcheck",
    ],
)

doxygen = Script(
    "doxygen",
    ["-q"],
)

trufflehog3 = Script("trufflehog3")

cspell = Script(
    "cspell",
    [".", "--dot", "--gitignore"],
    ["npx"],
)

prettier = Script(
    "prettier",
    [".", "--write"],
    ["npx"],
)

doxygen = Script(
    "doxygen",
    ["docs/doxygen/Doxyfile"],
)

breathe = Script(
    "breathe-apidoc",
    [
        "./docs/doxygen/dist",
        "--output-dir",
        "docs/sphinx/dist",
        "--members",
    ],
)

sphinx = Script(
    "sphinx-build",
    ["docs/sphinx", "docs/dist"],
)

cli = Tasks(
    [shared, tests],
    [
        Target("test", tests, ["--gtest_brief"]),
    ],
    [
        clang_format,
        clang_tidy,
        cppcheck,
        cppclean,
        cspell,
        doxygen,
        prettier,
        trufflehog3,
        doxygen,
        breathe,
        sphinx,
    ],
    [
        Routine("lint", [cspell, cppclean, cppcheck, trufflehog3]),
        Routine("format", [clang_format, prettier]),
        Routine("docs", [doxygen, breathe, sphinx]),
    ],
)

cli.register(env)
