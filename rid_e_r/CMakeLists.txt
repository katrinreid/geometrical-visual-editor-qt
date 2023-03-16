cmake_minimum_required(VERSION 3.23)
project(RationalLibrary)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
add_subdirectory(rational_library)
add_subdirectory(tests)

add_executable(RationalLibrary main.cpp)

target_link_libraries(RationalLibrary rational_library)