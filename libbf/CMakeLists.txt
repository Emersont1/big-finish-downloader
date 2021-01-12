project(BigFinish)
cmake_minimum_required(VERSION 3.10)

find_package(nlohmann_json REQUIRED)

include_directories(
    include
    ${CMAKE_SOURCE_DIR}/ext/lexbor/source
    ${CMAKE_SOURCE_DIR}/ext/cpr/include

    ${CMAKE_BINARY_DIR}/_deps/curl-src/include
)

add_library(bf SHARED
    src/login_req.cpp
    src/downloads.cpp
    src/downloads_parse.cpp
    src/downloads_scraper.cpp
)

target_link_libraries(bf
    cpr
    lexbor
    nlohmann_json::nlohmann_json
)