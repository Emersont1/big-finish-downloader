project(BigFinish)
cmake_minimum_required(VERSION 3.10)

include_directories(
    include
    ${CMAKE_SOURCE_DIR}/libbf/include
)

if(UNIX AND NOT APPLE)
find_package(PkgConfig REQUIRED)

pkg_search_module(LIBSECRET REQUIRED libsecret-1)
pkg_check_modules(GLIB REQUIRED glib-2.0)

include_directories(
    ${LIBSECRET_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
)

add_library(bf-os SHARED
    src/linux/libsecret/cookie_schema.cpp
    src/linux/libsecret/secret_storage.cpp
    src/linux/settings.cpp
)

target_link_libraries(bf-os
    bf
    ${LIBSECRET_LIBRARIES}
    ${GLIB_LIBRARIES}
)

include(${CMAKE_SOURCE_DIR}/gsettings.cmake)
add_schemas(bf-os "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
else()
add_library(bf-os SHARED
    src/none/os.cpp
)
target_link_libraries(bf-os
    bf
)
endif()