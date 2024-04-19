from miniscons import Build, Flag, Routine, Script, Target, Tasks, conan, flags
from SCons.Script.Main import GetOption
from walkmate import tree

env = conan(["gtest"])

tests = Build(
    "tests",
    tree("src", r"\.cpp$", ["main.cpp"]),
    flags(
        "c++11",
        [],
        [
            "deprecated-declarations",
            "macro-redefined",
            "missing-braces",
            "vla-extension",
        ],
    ),
)

clang_format = Script(
    "clang-format",
    ["-i", tree(".", r"\.(cpp|hpp|tpp)$")],
)

clang_tidy = Script(
    "clang-tidy",
    [tree("src", r"\.(cpp)$"), "--", [f"-I{i}" for i in env["CPPPATH"]]],
)

cppclean = Script("cppclean", ["."])
cppcheck = Script(
    "cppcheck",
    [
        tree("src", r"\.(cpp)$"),
        [f"-I{i}" for i in env["CPPPATH"]],
        [f"--suppress=*:{i}/*" for i in env["CPPPATH"]],
        "--quiet",
        "--enable=all",
        "--inline-suppr",
        "--suppressions-list=.cppcheck",
    ],
)

doxygen = Script("doxygen", ["-q"])
trufflehog3 = Script("trufflehog3")

cspell = Script("cspell", [".", "--dot"], ["npx"])
prettier = Script("prettier", [".", "--write"], ["npx"])

cli = Tasks(
    [tests],
    [Target("test", tests, ["--gtest_brief"])],
    [
        clang_format,
        clang_tidy,
        cppcheck,
        cppclean,
        cspell,
        doxygen,
        prettier,
        trufflehog3,
    ],
    [
        Routine("lint", [cspell, cppclean, cppcheck, clang_tidy, trufflehog3]),
        Routine("format", [clang_format, prettier]),
        Routine("docs", [doxygen]),
    ],
    [
        Flag("--iwyu"),
        Flag("--list"),
    ],
)

cli.register(env)

if GetOption("iwyu"):
    env["CXX"] = "include-what-you-use"

if GetOption("list"):
    cli.dump()
