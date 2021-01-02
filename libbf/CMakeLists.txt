project(BigFinish)
cmake_minimum_required(VERSION 3.10)

include_directories(
    include
    ${CMAKE_SOURCE_DIR}/lexbor/source
)

add_library(bf
    src/login.cpp
    src/downloads.cpp
    src/downloads_parse.cpp
    src/downloads_scraper.cpp
)

target_link_libraries(bf
    CONAN_PKG::cpr
    lexbor
)