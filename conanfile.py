import os
import shutil
from conan import ConanFile
from conan.tools.files import copy
from conan.tools.scons import SConsDeps


class Recipe(ConanFile):
    name = "caches"
    version = "0.1.0"

    def build_requirements(self):
        self.test_requires("gtest/1.12.1")

    def export_sources(self):
        for source in ["src/*.[cht]pp", "SConstruct.py"]:
            copy(self, source, self.recipe_folder, self.export_sources_folder)

    def generate(self):
        SConsDeps(self).generate()

    def package(self):
        copy(self, "*.[ht]pp", self.build_folder, f"{self.package_folder}/include")
        copy(self, "*", f"{self.build_folder}/dist", f"{self.package_folder}/lib")
        os.rename(
            f"{self.package_folder}/include/src",
            f"{self.package_folder}/include/{self.name}",
        )
