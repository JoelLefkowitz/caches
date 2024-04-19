import psutil
from functools import reduce
from miniscons import Build, Target, Tasks, conan, flags
from SCons.Script import SConscript
from walkmate import tree

env = conan(["gtest"])
tests = Build("tests", tree(".", r"\.cpp$"), flags("c++11"))

cli = Tasks([tests], [Target("test", tests, ["--gtest_brief"])])
cli.register(env)
