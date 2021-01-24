project(BigFinish)
cmake_minimum_required(VERSION 3.10)

find_package(nlohmann_json REQUIRED)
find_package(libzippp REQUIRED)
find_package(BZip2 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Pistache REQUIRED)
find_package(spdlog REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(
    include
    ${CMAKE_SOURCE_DIR}/libbf/include
    ${CMAKE_SOURCE_DIR}/big-finish-downloader-gtk/include
)

add_executable(big-finish-downloaderd
    src/main.cpp
    src/api_server/add_login.cpp
    src/api_server/errors.cpp
    src/api_server/get_queue.cpp
    src/api_server/get_status.cpp
    src/api_server/init.cpp
    src/server/download_loop.cpp
    src/server/init.cpp
    src/server/refresh_downloads.cpp

    ${CMAKE_SOURCE_DIR}/big-finish-downloader-gtk/src/zip.cpp
)

target_link_libraries(big-finish-downloaderd
    bf
    libzippp::libzippp
    pistache_static
    spdlog::spdlog
)

target_link_libraries(big-finish-downloaderd gcov pthread dl)