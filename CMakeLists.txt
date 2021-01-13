cmake_policy(SET CMP0048 NEW)

project(BigFinish VERSION 1.0.0)
cmake_minimum_required(VERSION 3.10)

# Use C++ 17
set(CMAKE_CXX_STANDARD 17)

configure_file("${CMAKE_SOURCE_DIR}/config.hpp.in" "${CMAKE_BINARY_DIR}/config.hpp")
include_directories(${CMAKE_BINARY_BIN})

include(${CMAKE_SOURCE_DIR}/pmm.cmake)
set(PACKAGES nlohmann-json libzippp)
if(WIN32)
list(APPEND PACKAGES openssl GTK curl)
endif()
pmm(VCPKG REVISION 2020.11 REQUIRES ${PACKAGES})

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE PATH "")
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/ib CACHE PATH "")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG2)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG2} ${CMAKE_BINARY_DIR}/bin CACHE PATH "")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG2} ${CMAKE_BINARY_DIR}/lib CACHE PATH "")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG2} ${CMAKE_BINARY_DIR}/lib CACHE PATH "")
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(WIN32)
set(VCPKG_DIR ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET} CACHE PATH "")
endif()

add_subdirectory(ext EXCLUDE_FROM_ALL)

add_subdirectory(libbf)
add_subdirectory(libbf-os)

add_subdirectory(big-finish-downloader-gtk)

option(BUILD_TESTS OFF "build Tests")
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

include(install.cmake)