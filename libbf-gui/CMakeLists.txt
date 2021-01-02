project(BigFinish)
cmake_minimum_required(VERSION 3.10)

find_package(PkgConfig REQUIRED)
pkg_search_module(LIBSECRET REQUIRED libsecret-1)

include(${CMAKE_SOURCE_DIR}/bin2h.cmake)

bin2h(SOURCE_FILE "glade/Login.glade" HEADER_FILE "${CMAKE_BINARY_DIR}/glade_login.hpp" VARIABLE_NAME "glade_login_str")


include_directories(
    include
    ${CMAKE_SOURCE_DIR}/libbf/include

    ${LIBSECRET_INCLUDE_DIRS}
)

add_library(bf-gui
    src/secret_storage.cpp
    src/cookie_schema.cpp
)

target_link_libraries(bf-gui
    bf
    ${LIBSECRET_LIBRARIES}
)
