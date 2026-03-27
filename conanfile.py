from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, cmake_layout


class os_learning(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def generate(self):
        tc = CMakeToolchain(self)
        cache_vars = {}
        for var, val in cache_vars.items():
            tc.cache_variables[var] = val
        tc.generate()

    def layout(self):
        self.folders.build_folder_vars = [
            "settings.compiler",
            "settings.compiler.version",
            "settings.build_type",
        ]
        cmake_layout(self)

    def requirements(self):
        sdl_version = "3.4.2"
        reqs = {
            "sdl": sdl_version,
            "glad": "0.1.36",
            "pugixml": "1.15",
            "fmt": "11.1.3",
            "frozen": "1.2.0",
            "boost": "1.87.0",
            "spdlog": "1.15.1",
        }  # defaults
        match self.settings.get_safe("os", None):
            case "Linux":
                reqs["sdl"] = "3.2.18"

            case "Windows":
                pass
            case _:
                pass

        for name, version in reqs.items():
            self.requires(f"{name}/{version}")  # type: ignore