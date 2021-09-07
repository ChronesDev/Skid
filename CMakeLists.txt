cmake_minimum_required(VERSION 3.20)
project(Skid)

set(CMAKE_CXX_STANDARD 20)

add_library(Skid SHARED Skid/Entry/Entry.cc)

add_subdirectory(Skid)