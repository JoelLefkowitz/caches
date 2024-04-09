import os
import re
import psutil
from SCons.Environment import Environment
from SCons.Script.Main import AddOption
from walkmate import get_child_files as tree

env = Environment(
    CXXFLAGS=["-std=c++11"],
    num_jobs=psutil.cpu_count(),
)

conan = SConscript("SConscript_conandeps")["conandeps"]
env.MergeFlags(conan)

sources = [
    "test.cpp",
    "test_caches.cpp",
]

env.Program("dist/tests", source=sources)
env.AlwaysBuild(env.Alias("test", ["dist/tests"], "dist/tests"))
