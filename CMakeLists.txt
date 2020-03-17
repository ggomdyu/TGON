cmake_minimum_required(VERSION 3.8)

project(TGON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(TGON_PATH ${CMAKE_CURRENT_LIST_DIR})
set(TGON_SOURCE_PATH ${TGON_PATH}/Source)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")

if(WIN32)
    set(TGON_PLATFORM_NAME "WINDOWS")
    set(TGON_GRAPHICS_NAME "OPENGL")
    set(TGON_UNIX_BASE_OS FALSE)
elseif(APPLE)
    set(TGON_GRAPHICS_NAME "OPENGL")
    set(TGON_UNIX_BASE_OS TRUE)
    set(CMAKE_CXX_FLAGS "-x objective-c++")
    if(IOS)
        set(TGON_PLATFORM_NAME "IOS")
    else()
        set(TGON_PLATFORM_NAME "MACOS")
    endif()
else()
    message(FATAL_ERROR "Your platform is not supported.")
endif()

if(WIN32)
    add_definitions(-DUNICODE -D_UNICODE)
endif()

function(init_source_subdirectories)
    add_subdirectory(${TGON_SOURCE_PATH})
endfunction()

init_source_subdirectories()