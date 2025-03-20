import os
import sys
import subprocess
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import shutil

class CMakeBuild(build_ext):
    """Custom build_ext command to compile the C++ extension using CMake."""
    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        build_temp = os.path.abspath(self.build_temp)

        # Remove any old build directory to avoid cached paths
        if os.path.exists(build_temp):
            shutil.rmtree(build_temp)
        os.makedirs(build_temp, exist_ok=True)

        # Use the directory containing setup.py as the project root
        project_root = os.path.abspath(os.path.dirname(__file__))
        print("Project root:", project_root)
        print("Build directory:", build_temp)
        print("Extension output directory:", extdir)

        cmake_args = [
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}",
            "-DCMAKE_CXX_STANDARD=17",
            f"-DPython_EXECUTABLE={sys.executable}",
            "-DCMAKE_CXX_FLAGS=-fPIC"
        ]
        print("Running CMake with arguments:", cmake_args)
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
    # Remove py_modules so that only the extension is installed
    ext_modules=[Extension("bioopt_python", sources=[])],
    cmdclass={"build_ext": CMakeBuild},
    install_requires=["numpy", "matplotlib"],
    options={"bdist_wheel": {"universal": False}},
    zip_safe=False,
)
