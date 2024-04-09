import os
import re
import psutil
from SCons.Environment import Environment
from SCons.Script.Main import AddOption
from walkmate import get_child_files as tree

env = Environment(
    CXXFLAGS=["-std=c++11"],
    ENV={"PATH": os.getenv("PATH")},
    num_jobs=psutil.cpu_count(),
)

conan = SConscript("SConscript_conandeps")["conandeps"]
env.MergeFlags(conan)

iwyu = AddOption("--iwyu", action="store_true")
find = lambda pattern: [source for source in tree(".") if re.search(pattern, source)]

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

sources = {
    "cpp": find(r"\.cpp$"),
    "all": find(r"\.(cpp|hpp|tpp)$"),
    "tests": find(r"test/.*\.cpp$"),
    "test_package": find(r"test_package/.*\.cpp$"),
}

targets = {
    "test": [sources["tests"], "--gtest_brief"],
}

flags = {
    "all": " ".join(sources["all"]),
    "tidy": " ".join([i for i in sources["cpp"] if not i in sources["test_package"]]),
    "includes": " ".join([f"-I{i}" for i in conan["CPPPATH"]]),
    "suppressions": " ".join([f"--suppress=*:{i}/*" for i in conan["CPPPATH"]]),
}

commands = {
    "clang-format": f"clang-format -i {flags['all']}",
    "clang-tidy": f"clang-tidy {flags['tidy']} -- {flags['includes']}",
    "cppcheck": f"cppcheck . --quiet --enable=all --inline-suppr --suppressions-list=.cppcheck {flags['includes']} {flags['suppressions']}",
    "cppclean": "cppclean .",
    "cspell": "npx cspell . --dot",
    "doxygen": "doxygen -q",
    "prettier": "npx prettier . --write",
    "trufflehog3": "trufflehog3 .",
}

aliases = {
    "docs": ["doxygen"],
    "lint": ["cspell", "cppclean", "cppcheck", "clang-tidy", "trufflehog3"],
    "format": ["clang-format", "prettier"],
}

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

if GetOption("iwyu"):
    env["CXX"] = "include-what-you-use"

else:
    env["CXX"] = "clang++"
    env["CXXFLAGS"].extend(warnings)
