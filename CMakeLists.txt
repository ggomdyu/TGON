cmake_minimum_required(VERSION 3.8)

project(TGON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(TGON_PATH ${CMAKE_CURRENT_LIST_DIR})
set(TGON_SOURCE_PATH ${TGON_PATH}/Source)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")

if (WIN32)
    set(TGON_PLATFORM_NAME "WINDOWS")
    set(TGON_GRAPHICS_NAME "OPENGL")
    set(TGON_UNIX_BASE_OS FALSE)
elseif (APPLE)
    set(TGON_GRAPHICS_NAME "OPENGL")
    set(TGON_UNIX_BASE_OS TRUE)
    set(CMAKE_CXX_FLAGS "-x objective-c++")
    set(TGON_PLATFORM_NAME "MACOS")
    if (IOS)
        set(TGON_PLATFORM_NAME "IOS")
    else ()
        set(TGON_PLATFORM_NAME "MACOS")
    endif ()
else ()
    message(FATAL_ERROR "Not supported platform!")
endif ()

function (init_global_properties)
    if (WIN32)
        add_definitions(-DUNICODE -D_UNICODE)
    endif ()
endfunction ()

function (init_tgon)
    add_subdirectory(${TGON_SOURCE_PATH})
    init_tgon_properties()
endfunction ()

function (init_tgon_properties)
    set_target_properties(TGON PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
    )

    target_compile_definitions(TGON PUBLIC 
        TGON_PLATFORM_${TGON_PLATFORM_NAME}=1 
        TGON_GRAPHICS_${TGON_GRAPHICS_NAME}=1
    )

    if (MSVC)
        target_compile_options(TGON PRIVATE
            /YcPrecompiledHeader.h /Oi
            $<$<CONFIG:Debug>:/ZI>
            $<$<CONFIG:Release>:>
        )
    endif()
endfunction ()

init_global_properties()
init_tgon()