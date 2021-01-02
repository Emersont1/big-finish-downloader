project(BigFinish)
cmake_minimum_required(VERSION 3.10)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

add_definitions(${GTK3_DEFINITIONS})

include_directories(
    ${CMAKE_SOURCE_DIR}/libbf/include
    ${CMAKE_SOURCE_DIR}/libbf-gui/include

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

add_executable(secret_store_test secret_store_test.cpp)
target_link_libraries(secret_store_test bf-gui)

add_executable(glade_login_test glade_login_test.cpp)
target_link_libraries(glade_login_test bf-gui ${GTK3_LIBRARIES})