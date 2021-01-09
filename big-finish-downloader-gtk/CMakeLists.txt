project(BigFinish)
cmake_minimum_required(VERSION 3.10)

find_package(PkgConfig)
if(${PkgConfig_FOUND})
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
else()
    find_package(GTK REQUIRED)
endif()

find_package(nlohmann_json REQUIRED)
find_package(libzippp REQUIRED)
find_package(BZip2 REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

include(${CMAKE_SOURCE_DIR}/bin2h.cmake)

bin2h(SOURCE_FILE "glade/Login.glade" HEADER_FILE "${CMAKE_BINARY_DIR}/glade_login.hpp" VARIABLE_NAME "glade_login_str")
bin2h(SOURCE_FILE "glade/Main.glade" HEADER_FILE "${CMAKE_BINARY_DIR}/glade_main.hpp" VARIABLE_NAME "glade_main_str")
bin2h(SOURCE_FILE "glade/Preferences.glade" HEADER_FILE "${CMAKE_BINARY_DIR}/glade_prefs.hpp" VARIABLE_NAME "glade_prefs_str")
bin2h(SOURCE_FILE "${CMAKE_SOURCE_DIR}/ext/db.json" HEADER_FILE "${CMAKE_BINARY_DIR}/db.hpp" VARIABLE_NAME "db_json")

include_directories(
    include
    ${CMAKE_SOURCE_DIR}/libbf/include
    ${CMAKE_SOURCE_DIR}/libbf-os/include
    ${CMAKE_SOURCE_DIR}/ext/cpr/include

    ${GTK3_INCLUDE_DIRS}
    ${BZIP2_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_BIN}/_deps/curl-src/include
)

add_executable(big-finish-downloader-gtk 
    src/main.cpp
    src/zip.cpp
    src/mime.cpp
    src/gui/alert_box.cpp
    src/gui/login.cpp
    src/gui/main_window/download.cpp
    src/gui/main_window/init.cpp
    src/gui/main_window/init/load_downloaded.cpp
    src/gui/main_window/init/widgets.cpp
    src/gui/main_window/update_func.cpp
    src/gui/main_window/get_images.cpp
    src/gui/main_window/callbacks/changed_dir.cpp
    src/gui/main_window/callbacks/close.cpp
    src/gui/main_window/callbacks/preferences.cpp
    src/gui/main_window/callbacks/toggle_cb.cpp
    src/gui/preferences_window/init.cpp
    src/gui/preferences_window/callbacks.cpp

    ${CMAKE_BINARY_DIR}/glade_login.hpp
    ${CMAKE_BINARY_DIR}/glade_main.hpp
)

target_link_libraries(big-finish-downloader-gtk
    libzippp::libzippp
    bf-os

    pthread
    dl
)
if(NOT WIN32)
target_link_libraries(big-finish-downloader-gtk ${GTK3_LIBRARIES})
else()
target_link_libraries(big-finish-downloader-gtk GTK)
endif()