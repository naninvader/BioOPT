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

        # ✅ Change working directory to the project root where CMakeLists.txt exists
        project_root = os.path.abspath(os.path.dirname(__file__))

        # Run CMake in the correct location
        subprocess.check_call(["cmake", project_root, f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}"], cwd=build_temp)
        subprocess.check_call(["cmake", "--build", ".", "--config", "Release"], cwd=build_temp)

setup(
    name="bioopt",
    version="0.1.0",
    author="Harrison Bitonti",
    description="Bio-inspired optimization library with SMA implementation",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    url="https://github.com/yourgithub/bioopt",
    packages=find_packages(where="src"),  # ✅ Ensure Python files are installed
    package_dir={"": "src"},
    package_data={"bioopt": ["bioopt_python*.so"]},  # ✅ Ensure .so file is included
    ext_modules=[Extension("bioopt_python", sources=[])],  # Placeholder for compiled .so file
    cmdclass={"build_ext": CMakeBuild},
    install_requires=["numpy", "torch", "matplotlib"],
)
