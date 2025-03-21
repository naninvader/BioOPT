import os
import sys
import subprocess
import shutil
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext

class CMakeBuild(build_ext):
    def build_extension(self, ext):
        # Where setuptools *wants* to place the final extension file
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        # Our separate build folder for CMake
        build_temp = os.path.abspath(self.build_temp)

        # Clean out old artifacts
        if os.path.exists(build_temp):
            shutil.rmtree(build_temp)
        os.makedirs(build_temp, exist_ok=True)

        project_root = os.path.abspath(os.path.dirname(__file__))

        # Pass the library output directory to CMake
        cmake_args = [
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={os.path.join(build_temp, 'lib')}",
            "-DCMAKE_CXX_STANDARD=17",
            f"-DPython_EXECUTABLE={sys.executable}",
            "-DCMAKE_CXX_FLAGS=-fPIC"
        ]

        # Configure and build via CMake
        subprocess.check_call(["cmake", project_root] + cmake_args, cwd=build_temp)
        subprocess.check_call(["cmake", "--build", ".", "--config", "Release"], cwd=build_temp)

        # The compiled .so is placed here by CMake:
        built_lib_path = os.path.join(build_temp, "lib", "bioopt.so")

        # The final location where setuptools expects it
        final_output_path = self.get_ext_fullpath(ext.name)
        # Ensure the parent dir exists (since we have no .py files)
        os.makedirs(os.path.dirname(final_output_path), exist_ok=True)

        print(f"Copying {built_lib_path} -> {final_output_path}")
        self.copy_file(built_lib_path, final_output_path)

setup(
    name="bioopt",
    version="0.1.0",
    description="Bio-inspired optimization library",
    # Build the extension named "bioopt", so `import bioopt` works
    ext_modules=[Extension("bioopt", sources=[])],
    cmdclass={"build_ext": CMakeBuild},
    install_requires=["numpy", "matplotlib"],
    options={"bdist_wheel": {"universal": False}},
    zip_safe=False,
)
