import psutil
from functools import reduce
from miniscons import Build, Target, Tasks, conan, flags
from SCons.Script import SConscript
from walkmate import tree

env, includes = conan()
tests = Build("tests", tree(".", r"\.cpp$"), flags("c++11"), ["gtest"])

cli = Tasks([tests], [Target("test", tests, ["--gtest_brief"])])
cli.register(env)
