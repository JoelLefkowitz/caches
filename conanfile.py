from conan import ConanFile
from conan.tools.files import copy
from conan.tools.scons import SConsDeps


class Recipe(ConanFile):
    name = "caches"
    version = "0.1.0"

    def build_requirements(self):
        self.test_requires("gtest/1.12.1")

    def export_sources(self):
        for source in [
            "conanfile.py",
            "SConstruct.py",
            "src/*.[cht]pp",
        ]:
            copy(
                self,
                source,
                self.recipe_folder,
                self.export_sources_folder,
            )

    def generate(self):
        SConsDeps(self).generate()

    def package(self):
        copy(
            self,
            "*.[ht]pp",
            f"{self.build_folder}/src",
            f"{self.package_folder}/include/{self.name}",
        )
        copy(
            self,
            "*.a",
            f"{self.build_folder}/dist",
            f"{self.package_folder}/lib",
        )
