import os
import sys
import subprocess
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext

class CMakeBuild(build_ext):
    """Custom build_ext command to compile the C++ extension using CMake."""
    def build_extension(self, ext):
        # Get the absolute directory for the extension module output
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        build_temp = os.path.abspath(self.build_temp)
        
        # Ensure build directory exists
        os.makedirs(build_temp, exist_ok=True)
        
        # Determine the project root (where CMakeLists.txt is located)
        project_root = os.path.abspath(os.path.dirname(__file__))
        
        # Set up CMake arguments, explicitly passing the Python executable and forcing -fPIC
        cmake_args = [
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}",
            "-DCMAKE_CXX_STANDARD=17",
            f"-DPython_EXECUTABLE={sys.executable}",
            "-DCMAKE_CXX_FLAGS=-fPIC"
        ]
        
        # Run CMake in the build directory with the project root as the source directory
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
    # Do not use find_packages because no Python package directory exists.
    # We are only installing the C++ extension module.
    ext_modules=[Extension("bioopt_python", sources=[])],
    cmdclass={"build_ext": CMakeBuild},
    install_requires=["numpy", "matplotlib"],
    options={"bdist_wheel": {"universal": False}},
)
