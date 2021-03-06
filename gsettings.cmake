option(GSETTINGS_COMPILE "Compile GSettings schemas. Can be disabled for packaging reasons." ON)
option(GSETTINGS_COMPILE_IN_PLACE "Compile GSettings schemas in the build folder. This is used for running an appliction without installing the GSettings systemwide.  The application will need to set GSETTINGS_SCHEMA_DIR" ON)

if (GSETTINGS_COMPILE)
    message(STATUS "GSettings schemas will be compiled.")
endif ()

if (GSETTINGS_COMPILE_IN_PLACE)
    message(STATUS "GSettings schemas will be compiled in-place.")
endif ()

macro(add_schemas GSETTINGS_TARGET SCHEMA_DIRECTORY PREFIX GLIB_TOOL)
    find_package(PkgConfig)
    
    # Locate all schema files.
    file(GLOB all_schema_files
        "${SCHEMA_DIRECTORY}/*.gschema.xml"
    )
    
    if ("${PREFIX}" STREQUAL "")
        # Find the GLib path for schema installation
        execute_process(
            COMMAND
                ${PKG_CONFIG_EXECUTABLE}
                glib-2.0
                --variable prefix
            OUTPUT_VARIABLE
                _glib_prefix
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    else ()
        set(_glib_prefix ${PREFIX})
    endif ()
    
    set(GSETTINGS_DIR "${_glib_prefix}/share/glib-2.0/schemas/" CACHE INTERNAL "")
    
    # Fetch path for schema compiler from pkg-config
    if ("${GLIB_TOOL}" STREQUAL "")
        execute_process(
            COMMAND
                ${PKG_CONFIG_EXECUTABLE}
                gio-2.0
                --variable
                glib_compile_schemas
            OUTPUT_VARIABLE
                _glib_compile_schemas
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    
        set(glib_schema_compiler ${_glib_compile_schemas} CACHE INTERNAL "")
    else()
        set(glib_schema_compiler ${GLIB_TOOL} CACHE INTERNAL "")
    endif()

    if (GSETTINGS_COMPILE_IN_PLACE)
        set(COMPILE_IN_PLACE_DIR ${CMAKE_BINARY_DIR}/gsettings)
    else ()
        set(COMPILE_IN_PLACE_DIR ${GSETTINGS_DIR})
    endif ()
    add_custom_command(
        TARGET
            ${GSETTINGS_TARGET}
        COMMAND 
            ${CMAKE_COMMAND} -E make_directory "${COMPILE_IN_PLACE_DIR}"
    )
        
    # Copy all schemas to the build folder.
    foreach(schema_file ${all_schema_files})
        add_custom_command(
            TARGET
                ${GSETTINGS_TARGET}
            COMMAND 
                ${CMAKE_COMMAND} -E copy "${schema_file}" "${COMPILE_IN_PLACE_DIR}"
            COMMENT "Copying schema ${schema_file} to ${COMPILE_IN_PLACE_DIR}"
        )
    endforeach()
     
    # Compile schema in-place.
    add_custom_command(
        TARGET 
            ${GSETTINGS_TARGET}
        COMMAND
            ${glib_schema_compiler} ${COMPILE_IN_PLACE_DIR}
            
        COMMENT "Compiling schemas in folder: ${COMPILE_IN_PLACE_DIR}"
    )

endmacro(add_schemas)
