import os

from conan import ConanFile
from conan.tools.files import copy
from conan.tools.scons import SConsDeps
from conan.tools.layout import basic_layout


class CachesConan(ConanFile):
    name = "caches"
    description = "Extensible cache templates."
    version = "0.4.0"
    license = "MIT"

    url = "https://github.com/conan-io/conan-center-index"
    homepage = "https://github.com/JoelLefkowitz/caches"

    topics = (
        "cache",
        "fifo",
        "lifo",
        "lru",
        "header-only",
    )

    package_type = "header-library"
    settings = (
        "os",
        "arch",
        "compiler",
        "build_type",
    )

    no_copy_source = True
    exports = "src/*"

    def layout(self):
        basic_layout(self, src_folder="src")

    def generate(self):
        SConsDeps(self).generate()

    def package_id(self):
        self.info.clear()

    def build_requirements(self):
        self.test_requires("gtest/1.12.1")

    def build(self):
        pass

    def package(self):
        copy(
            self,
            "LICENSE.md",
            self.recipe_folder,
            os.path.join(self.package_folder, "licenses"),
        )
        copy(
            self,
            "*.[ht]pp",
            os.path.join(self.recipe_folder, "src"),
            os.path.join(self.package_folder, "include", self.name),
        )

    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
