project(BigFinish)
cmake_minimum_required(VERSION 3.10)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(
    ${CMAKE_SOURCE_DIR}/libbf/include

    ${CMAKE_BINARY_DIR}
    ${GTK3_INCLUDE_DIRS}
)

add_executable(json_test json_test.cpp)

add_executable(login_test login_test.cpp)
target_link_libraries(login_test bf)

add_executable(downloads_test downloads_test.cpp)
target_link_libraries(downloads_test bf)

add_executable(download_file_test download_file_test.cpp)
target_link_libraries(download_file_test bf)

add_executable(glade_login_test glade_login_test.cpp)
target_link_libraries(glade_login_test ${GTK3_LIBRARIES})

add_executable(api_login_test api_login_test.cpp)
target_link_libraries(api_login_test cpr)