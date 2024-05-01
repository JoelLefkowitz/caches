from miniscons import Build, Target, Tasks, conan, flags, packages
from walkmate import tree

env = conan()

tests = Build(
    "tests",
    tree("src", r"\.cpp$", ["main.cpp"]),
    flags("c++11"),
    packages(["gtest"]),
)

cli = Tasks(
    [tests],
    [Target("test", tests, ["--gtest_brief"])],
)

cli.register(env)
