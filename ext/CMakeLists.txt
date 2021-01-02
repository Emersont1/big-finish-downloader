project(BigFinish)
cmake_minimum_required(VERSION 3.10)

set(USE_OPENSSL ON CACHE BOOL "")
set(USE_SYSTEM_CURL ON CACHE BOOL "")
set(BUILD_CPR_TESTS OFF CACHE BOOL "")
add_subdirectory(cpr)

add_subdirectory(lexbor)