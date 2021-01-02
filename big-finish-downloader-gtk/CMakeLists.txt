project(BigFinish)
cmake_minimum_required(VERSION 3.10)

find_package(PkgConfig REQUIRED)
pkg_search_module(LIBSECRET REQUIRED libsecret-1)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include(${CMAKE_SOURCE_DIR}/bin2h.cmake)

bin2h(SOURCE_FILE "glade/Login.glade" HEADER_FILE "${CMAKE_BINARY_DIR}/glade_login.hpp" VARIABLE_NAME "glade_login_str")
bin2h(SOURCE_FILE "glade/Main.glade" HEADER_FILE "${CMAKE_BINARY_DIR}/glade_main.hpp" VARIABLE_NAME "glade_main_str")


include_directories(
    include
    ${CMAKE_SOURCE_DIR}/libbf/include

    ${LIBSECRET_INCLUDE_DIRS}
    ${GTK3_INCLUDE_DIRS}
    ${CMAKE_BINARY_DIR}
)

add_executable(big-finish-downloader-gtk 
    src/main.cpp
    src/libsecret/cookie_schema.cpp
    src/libsecret/secret_storage.cpp
    src/gui/login.cpp
    src/gui/main_window/init.cpp
    src/gui/main_window/callbacks/close.cpp

    ${CMAKE_BINARY_DIR}/glade_login.hpp
    ${CMAKE_BINARY_DIR}/glade_main.hpp
)

target_link_libraries(big-finish-downloader-gtk
    bf
    ${LIBSECRET_LIBRARIES}
    ${GTK3_LIBRARIES}    
)