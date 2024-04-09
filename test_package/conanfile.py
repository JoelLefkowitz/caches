import os
from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.build import can_run
from conan.tools.files import copy
from conan.tools.scons import SConsDeps


class Conan(ConanFile):
    requires = ["gtest/1.12.1"]
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires(self.tested_reference_str)

    def generate(self):
        SConsDeps(self).generate()

    def test(self):
        if can_run(self):
            self.run("scons test")
