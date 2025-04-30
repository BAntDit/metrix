
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

class metatrixReceip(ConanFile):
    name = "metrix"
    version = "1.5.0.0"
    url = "https://github.com/BAntDit/easy-mp"
    description = "Meta programming tricks library"

    settings = "arch", "build_type", "compiler", "os"

    exports_sources = "CMakeLists.txt", "*.cmake", ".clang-format", ".md", "src/*.h", "tests/*", "cmake/*"

    def requirements(self):
        self.requires("gtest/[~1.16]")

    def configure(self):
        if self.settings.compiler == "msvc":
            del self.settings.compiler.runtime

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)

        if self.settings.os == "Windows":
            if self.settings.compiler == "msvc":
                tc.generator = "Visual Studio 17 2022"
            else:
                try:
                    tc.generator = "Ninja"
                except:
                    tc.generator = "Unix Makefiles"
        else:
            try:
                tc.generator = "Ninja"
            except:
                tc.generator = "Unix Makefiles"

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "metrix")
        self.cpp_info.set_property("cmake_target_name", "metrix::metrix")

        # For header-only libraries, no libs needed
        self.cpp_info.libs = []


