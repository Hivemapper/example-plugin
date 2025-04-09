cmake_minimum_required(VERSION 3.10)
project(example_plugin)

# <---------- set c++ standard ------------->
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(lib/hive-cpp)
add_subdirectory(src)