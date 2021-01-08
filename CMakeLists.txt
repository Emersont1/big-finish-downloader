cmake_policy(SET CMP0048 NEW)

project(BigFinish VERSION 0.0.1)
cmake_minimum_required(VERSION 3.10)

# Use C++ 17
set(CMAKE_CXX_STANDARD 17)

configure_file("${CMAKE_SOURCE_DIR}/config.hpp.in" "${CMAKE_BINARY_DIR}/config.hpp")
include_directories(${CMAKE_BINARY_BIN})

include(${CMAKE_SOURCE_DIR}/pmm.cmake)
pmm(CONAN DEBUG)

add_subdirectory(ext)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(libbf)
add_subdirectory(libbf-os)

add_subdirectory(big-finish-downloader-gtk)

add_subdirectory(tests)