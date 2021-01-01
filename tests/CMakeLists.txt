project(BigFinish)
cmake_minimum_required(VERSION 3.10)

include_directories(
    ${CMAKE_SOURCE_DIR}/libbf/include
)

add_executable(json_test json_test.cpp)

add_executable(login_test login_test.cpp)
target_link_libraries(login_test bf)

add_executable(downloads_test downloads_test.cpp)
target_link_libraries(downloads_test bf)