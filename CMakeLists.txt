cmake_minimum_required(VERSION 3.20)
project(Skid)

set(CMAKE_CXX_STANDARD 20)

# Remove Windows.h shit
add_compile_definitions(WIN32_LEAN_AND_MEAN)
add_compile_definitions(NOMINMAX)

add_library(Skid SHARED Skid/Entry/Entry.cc)

add_subdirectory(Skid)