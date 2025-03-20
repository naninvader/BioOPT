cmake_minimum_required(VERSION 3.10)
project(BioOPT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -D_GLIBCXX_USE_CXX11_ABI=0")

find_package(Python COMPONENTS Interpreter Development REQUIRED)
set(Python_EXECUTABLE ${Python_EXECUTABLE})

include_directories(${Python_INCLUDE_DIRS} /usr/local/lib/python3.11/dist-packages/pybind11/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(bioopt_python SHARED 
    src/bindings/bindings.cpp 
    src/core/optimizer.cpp 
    src/algorithms/sma.cpp
)

# Force the output name to be exactly "bioopt_python" with no prefix
set_target_properties(bioopt_python PROPERTIES PREFIX "" OUTPUT_NAME "bioopt_python")

target_include_directories(bioopt_python PRIVATE ${Python_INCLUDE_DIRS})
target_link_libraries(bioopt_python PRIVATE ${Python_LIBRARIES})
