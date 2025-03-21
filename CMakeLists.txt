cmake_minimum_required(VERSION 3.10)
project(BioOPT)

# Option for toggling Colab-specific settings
option(COLAB "Build for Google Colab environment" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if(COLAB)
    message(STATUS "Building for Google Colab: enabling old cxx11 ABI and special includes.")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")
    include_directories(/usr/local/lib/python3.11/dist-packages/pybind11/include)
endif()

# Find Python interpreter and development libraries
find_package(Python COMPONENTS Interpreter Development REQUIRED)
set(Python_EXECUTABLE ${Python_EXECUTABLE})

# Ensure the compiler sees your include/ directory for base_optimizer.h, sma.h, pso.h, ga.h, etc.
include_directories(${CMAKE_SOURCE_DIR}/include)

# Where the compiled library (bioopt.so) will be placed
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

# Link Python libraries
target_include_directories(bioopt PRIVATE ${Python_INCLUDE_DIRS})
target_link_libraries(bioopt PRIVATE ${Python_LIBRARIES})
