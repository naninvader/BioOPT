cmake_minimum_required(VERSION 3.10)
project(BioOPT)

# Option for toggling Colab-specific settings
option(COLAB "Build for Google Colab environment" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if(COLAB)
    message(STATUS "Building for Google Colab: enabling old cxx11 ABI and Colab-specific settings.")
    # Enable the old C++ ABI
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")
endif()

# Find Python interpreter and development libraries
find_package(Python COMPONENTS Interpreter Development REQUIRED)
set(Python_EXECUTABLE ${Python_EXECUTABLE})

# Try to find pybind11 via CMake.
find_package(pybind11 QUIET)

if(pybind11_FOUND)
    message(STATUS "Found pybind11: ${pybind11_INCLUDE_DIRS}")
else()
    message(WARNING "pybind11 not found via find_package; using COLAB-specific include directory")
    if(COLAB)
        include_directories(/usr/local/lib/python3.11/dist-packages/pybind11/include)
    else()
        message(FATAL_ERROR "pybind11 not found. Please install it (e.g., pip install pybind11) or set the include directory manually.")
    endif()
endif()

# Ensure the compiler sees your include/ directory for BioOPT headers.
include_directories(${CMAKE_SOURCE_DIR}/include)

# Where the compiled library (bioopt.so) will be placed.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Build a shared library named "bioopt"
add_library(bioopt SHARED
    src/bindings/bindings.cpp
    src/core/optimizer.cpp
    src/algorithms/sma.cpp
    src/algorithms/pso.cpp
    src/algorithms/ga.cpp
)

# Force the library name to be "bioopt" (no "lib" prefix)
set_target_properties(bioopt PROPERTIES
    PREFIX ""
    OUTPUT_NAME "bioopt"
)

# If pybind11 was found, link it to our module.
if(pybind11_FOUND)
    target_link_libraries(bioopt PRIVATE pybind11::module)
endif()

# Link Python libraries.
target_include_directories(bioopt PRIVATE ${Python_INCLUDE_DIRS})
target_link_libraries(bioopt PRIVATE ${Python_LIBRARIES})
