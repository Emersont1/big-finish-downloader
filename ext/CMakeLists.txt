project(BigFinish)
cmake_minimum_required(VERSION 3.10)

set(BUILD_CPR_TESTS OFF CACHE BOOL "")
add_subdirectory(cpr)

add_subdirectory(lexbor)