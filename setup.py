import os
import sys
import subprocess
from setuptools import setup, find_packages, Extension
from setuptools.command.build_ext import build_ext

class CMakeBuild(build_ext):
    """Custom build_ext to compile the C++ extension using CMake."""
    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        build_temp = os.path.abspath(self.build_temp)

        # Ensure build directory exists
        os.makedirs(build_temp, exist_ok=True)

        # ✅ Detect project root where CMakeLists.txt is located
        project_root = os.path.abspath(os.path.dirname(__file__))

        # ✅ Set CMake arguments to handle Python paths correctly
        cmake_args = [
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}",
            "-DCMAKE_CXX_STANDARD=17",
            f"-DPython_EXECUTABLE={sys.executable}",
            "-DCMAKE_CXX_FLAGS=-fPIC"
        ]

        # ✅ Run CMake in the correct directory
        subprocess.check_call(["cmake", project_root] + cmake_args, cwd=build_temp)
        subprocess.check_call(["cmake", "--build", ".", "--config", "Release"], cwd=build_temp)

setup(
    name="bioopt",
    version="0.1.0",
    author="Harrison Bitonti",
    description="Bio-inspired optimization library with SMA implementation",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    url="https://github.com/naninvader/BioOPT",
    packages=find_packages(where="src"),
    package_dir={"": "src"},
    package_data={"bioopt": ["bioopt_python*.so"]},  # ✅ Ensure .so is included
    ext_modules=[Extension("bioopt_python", sources=[])],  # Placeholder for compiled .so file
    cmdclass={"build_ext": CMakeBuild},
    install_requires=["numpy", "torch", "matplotlib"],
    options={"bdist_wheel": {"universal": False}},  # ✅ Forces direct installation (skip wheels)
)
