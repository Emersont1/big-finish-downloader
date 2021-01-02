project(BigFinish)
cmake_minimum_required(VERSION 3.10)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(
    include
    ${CMAKE_SOURCE_DIR}/libbf/include
    ${CMAKE_SOURCE_DIR}/libbf-gui/include

    ${CMAKE_BINARY_DIR}
    ${GTK3_INCLUDE_DIRS}
)

add_executable(big-finish-downloader-gtk 
    src/ui/login.cpp

    src/main.cpp
)

target_link_libraries(big-finish-downloader-gtk  bf-gui ${GTK3_LIBRARIES})