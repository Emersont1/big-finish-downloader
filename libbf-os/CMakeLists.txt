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
        src/linux/dirs.cpp
    )
elseif(WIN32)
    list(APPEND SOURCES
        src/windows/dirs.cpp
        src/windows/secrets.cpp
    )
else()
    list(APPEND SOURCES  src/none/secrets.cpp)
endif()

add_library(bf-os SHARED
    ${SOURCES}
)


include(${CMAKE_SOURCE_DIR}/gsettings.cmake)

if(NOT WIN32)
    target_link_libraries(bf-os
        bf
        ${LIBSECRET_LIBRARIES}
        ${GLIB_LIBRARIES}
    )
    set(GSETTINGS_COMPILE_IN_PLACE OFF CACHE BOOL "" FORCE)
    add_schemas(bf-os "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" "")
else()
    target_link_libraries(bf-os
        bf
        ${VCPKG_DIR}/lib/gio-2.0.lib
    )
    message(${VCPKG_DIR})

    set(GSETTINGS_COMPILE_IN_PLACE OFF CACHE BOOL "" FORCE)
    add_schemas(bf-os "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" "${VCPKG_DIR}/tools/glib/glib-compile-schemas.exe")
endif()

