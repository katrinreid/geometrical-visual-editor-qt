cmake_minimum_required(VERSION 3.23)
project(RationalLibrary)

set(CMAKE_CXX_STANDARD 20)

add_executable(tests doctest.cpp)

target_link_libraries(tests rational_library)