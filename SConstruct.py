import os
import re
import psutil
from SCons.Environment import Environment
from SCons.Script.Main import AddOption
from walkmate import get_child_files as tree

CPPPATH = os.getenv("CPPPATH", "/usr/local/include")
LIBPATH = os.getenv("LIBPATH", "/usr/local/lib")

libs = [
    "gtest",
    "pthread",
]

warnings = [
    "-Wall",
    "-Wconversion",
    "-Wextra",
    "-Wfatal-errors",
    "-Wmissing-declarations",
    "-Wpedantic",
    "-Wshadow-uncaptured-local",
    "-Wshadow",
    "-Wno-deprecated-declarations",
    "-Wno-macro-redefined",
    "-Wno-missing-braces",
    "-Wno-pessimizing-move",
    "-Wno-unused-parameter",
    "-Wno-vla-extension",
]

find = lambda pattern: [source for source in tree(".") if re.search(pattern, source)]

sources = {
    "cpp": find(r".(cpp)$"),
    "all": find(r".(cpp|hpp|tpp)$"),
}

targets = {
    "test": [sources["cpp"], "--gtest_brief"],
}

commands = {
    "clang-format": f"clang-format -i {' '.join(sources['all'])}",
    "clang-tidy": f"clang-tidy {' '.join(sources['cpp'])} -- -I{CPPPATH}",
    "cppcheck": "cppcheck . --quiet --enable=all --inline-suppr --suppressions-list=.cppcheck",
    "cppclean": "cppclean .",
    "cspell": "npx cspell . --dot",
    "prettier": "npx prettier . --write",
    "trufflehog3": "trufflehog3 .",
    "doxygen": "doxygen",
}

aliases = {
    "docs": [
        "doxygen",
    ],
    "lint": [
        "cspell",
        "cppclean",
        "cppcheck",
        "clang-tidy",
        "trufflehog3",
    ],
    "format": [
        "clang-format",
        "prettier",
    ],
}

env = Environment(
    LIBS=libs,
    ENV={"PATH": os.getenv("PATH")},
    CPPPATH=CPPPATH,
    LIBPATH=LIBPATH,
    CXXFLAGS=["-std=c++11"],
    num_jobs=psutil.cpu_count(),
)

iwyu = AddOption(
    "--iwyu",
    action="store_true",
)

for [name, [sources, flags]] in targets.items():
    build = f"build-{name}"
    target = os.path.join("dist", name)
    env.Program(target, source=sources)
    env.Alias(build, target)
    env.AlwaysBuild(env.Alias(name, [build], f"{target} {flags}"))

for [name, command] in commands.items():
    env.AlwaysBuild(env.Alias(name, [], command))

for [name, commands] in aliases.items():
    env.AlwaysBuild(env.Alias(name, commands))

if env["PLATFORM"] == "win32":
    env.Tool("mingw")
    env["LIBS"].remove("pthread")

elif GetOption("iwyu"):
    env["CXX"] = "include-what-you-use"

else:
    env["CXX"] = "clang++"
    env["CXXFLAGS"].extend(warnings)
