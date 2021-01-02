project(BigFinish)
cmake_minimum_required(VERSION 3.10)

# Use C++ 17
set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_SOURCE_DIR}/pmm.cmake)
pmm(CONAN DEBUG)

add_subdirectory(ext)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(libbf)

add_subdirectory(big-finish-downloader-gtk)

add_subdirectory(tests)