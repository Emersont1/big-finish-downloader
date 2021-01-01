project(BigFinish)
cmake_minimum_required(VERSION 3.10)

include_directories(
    include
)

add_library(bf
    src/login.cpp
    src/downloads.cpp
    src/downloads_scraper.cpp
)

target_link_libraries(bf
    CONAN_PKG::cpr
    CONAN_PKG::tinyxml2
)