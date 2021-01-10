project(BigFinish)
cmake_minimum_required(VERSION 3.10)

include_directories(
    include
    ${CMAKE_SOURCE_DIR}/libbf/include
)

find_package(PkgConfig)
if(${PkgConfig_FOUND})
    pkg_search_module(LIBSECRET REQUIRED libsecret-1)
    pkg_check_modules(GLIB REQUIRED glib-2.0)
else()
    find_package(GLib REQUIRED)
endif()

include_directories(
    ${LIBSECRET_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
    ${BZIP2_INCLUDE_DIR}
)
set(SOURCES
    src/settings.cpp
)
if(UNIX AND NOT MACOSX)
    list(APPEND SOURCES
        src/linux/libsecret/cookie_schema.cpp
        src/linux/libsecret/secret_storage.cpp
    )
else()
    list(APPEND SOURCES  src/none.cpp)
endif()

add_library(bf-os SHARED
    ${SOURCES}
)

target_link_libraries(bf-os
    bf
    ${LIBSECRET_LIBRARIES}
    ${GLIB_LIBRARIES}
)

include(${CMAKE_SOURCE_DIR}/gsettings.cmake)
add_schemas(bf-os "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
