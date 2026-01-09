
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.errors import ConanInvalidConfiguration

class metatrixReceip(ConanFile):
    name = "metrix"
    version = "1.8.1.0"
    url = "https://github.com/BAntDit/metrix"
    description = "Meta programming tricks library"

    settings = "os", "compiler", "arch", "build_type"

    exports_sources = "CMakeLists.txt", "*.cmake", ".clang-format", ".md", "src/*.h", "tests/*", "cmake/*"

    def validate(self):
        if self.settings.compiler == "msvc":
            if int(str(self.settings.compiler.version)) < 192:
                raise ConanInvalidConfiguration("Only Visual Studio 2019 (MSVC 16) and higher is supported!")

    def build_requirements(self):
        if self.settings.compiler != "msvc":
            self.tool_requires("ninja/[>=1.11.0]")

    def requirements(self):
        self.requires("gtest/[~1.16]")

    def configure(self):
        self.settings.compiler.cppstd = "20"

    def package_id(self):
        self.info.settings.compiler.cppstd = "20"

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)

        if self.settings.compiler == "msvc":
            tc.generator = "Visual Studio 17 2022"
        else:
            tc.generator = "Ninja"

        tc.variables["REQUIRED_CXX_STANDARD"] = "20"
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


