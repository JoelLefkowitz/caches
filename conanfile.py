import os
from conan import ConanFile
from conan.tools.files import copy
from conan.tools.scons import SConsDeps


class Conan(ConanFile):
    name = "caches"
    version = "0.1.0"

    requires = ["gtest/1.12.1"]
    settings = ["os", "arch", "compiler", "build_type"]

    exports_sources = ["include/*"]
    no_copy_source = True

    def generate(self):
        SConsDeps(self).generate()

    def package(self):
        copy(
            self,
            "*.[ht]pp",
            self.source_folder,
            os.path.join(self.package_folder, "include/caches"),
            keep_path=False,
        )

    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
