
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

class metatrixReceip(ConanFile):
    name = "metrix"
    version = "1.5.0.0"
    description = "Meta programming tricks library"

    settings = "build_type"

    exports_sources = "CMakeLists.txt", "src/*.h"

    def requirements(self):
        self.requires("gtest/[~1.16]")

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["metrix"]


