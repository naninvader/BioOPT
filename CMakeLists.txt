cmake_minimum_required(VERSION 3.10)
project(BioOPT)

# Set the C++ standard and flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -D_GLIBCXX_USE_CXX11_ABI=0")

# Find Python and get its include directories
find_package(Python COMPONENTS Interpreter Development REQUIRED)
set(Python_EXECUTABLE ${Python_EXECUTABLE})

# Manually add the pybind11 include directory from the pip installation in Colab
include_directories(${Python_INCLUDE_DIRS} /usr/local/lib/python3.11/dist-packages/pybind11/include)

# Also include your project's own header directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Set the output directory for the shared library
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Define the shared library for Python bindings, including the necessary source files
add_library(bioopt_python SHARED 
    src/bindings/bindings.cpp 
    src/core/optimizer.cpp 
    src/algorithms/sma.cpp
)

# Force the output library name to be exactly "bioopt_python" with no prefix
set_target_properties(bioopt_python PROPERTIES PREFIX "" OUTPUT_NAME "bioopt_python")

# Ensure that the Python include directories are used for this library
target_include_directories(bioopt_python PRIVATE ${Python_INCLUDE_DIRS})

# Link the Python libraries
target_link_libraries(bioopt_python PRIVATE ${Python_LIBRARIES})
