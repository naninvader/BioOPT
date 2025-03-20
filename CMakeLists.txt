cmake_minimum_required(VERSION 3.10)
project(BioOPT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -D_GLIBCXX_USE_CXX11_ABI=0")

# ✅ Automatically detect Python executable (important for Colab)
find_package(Python COMPONENTS Interpreter Development REQUIRED)
set(Python_EXECUTABLE ${Python_EXECUTABLE})

# ✅ Set output directory for shared libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ✅ Include directories
include_directories(${Python_INCLUDE_DIRS})
include_directories(include)

# ✅ Define shared library for Python bindings
add_library(bioopt_python SHARED 
    src/bindings/bindings.cpp 
    src/core/optimizer.cpp 
    src/algorithms/sma.cpp
)

# ✅ Link Python library
target_include_directories(bioopt_python PRIVATE ${Python_INCLUDE_DIRS})
target_link_libraries(bioopt_python PRIVATE ${Python_LIBRARIES})
