cmake_minimum_required(VERSION 3.10)
project(BioOPT)

set(CMAKE_CXX_STANDARD 17)  
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti")

# Set the Python executable from the virtual environment (if needed)
set(Python_EXECUTABLE /home/harrisonbitonti/bioopt_env/bin/python)

# Find Pybind11
find_package(pybind11 REQUIRED)

# Build the Python extension module
pybind11_add_module(bioopt_python
    src/bindings/bindings.cpp
    src/algorithms/sma.cpp
    src/core/optimizer.cpp
)

target_include_directories(bioopt_python PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${pybind11_INCLUDE_DIRS}
)
