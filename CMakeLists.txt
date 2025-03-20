cmake_minimum_required(VERSION 3.10)
project(BioOPT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -D_GLIBCXX_USE_CXX11_ABI=0")

# ✅ Ensure correct Python version is detected
find_package(Python COMPONENTS Interpreter Development REQUIRED)
set(Python_EXECUTABLE ${Python_EXECUTABLE})

# ✅ Manually specify Pybind11 include directory (needed for Colab)
include_directories(/usr/local/lib/python3.11/dist-packages/pybind11/include)

# ✅ Set correct include paths
include_directories(${Python_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)  # Ensures headers are found

# ✅ Set output directory for shared libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ✅ Define shared library for Python bindings
add_library(bioopt_python SHARED 
    src/bindings/bindings.cpp 
    src/core/optimizer.cpp 
    src/algorithms/sma.cpp
)

# ✅ Link Python and Pybind11
target_include_directories(bioopt_python PRIVATE ${Python_INCLUDE_DIRS})
target_link_libraries(bioopt_python PRIVATE ${Python_LIBRARIES})
