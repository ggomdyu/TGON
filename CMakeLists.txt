cmake_minimum_required(VERSION 3.8)

project(TGON)

# Define variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(TGON_PATH ${CMAKE_CURRENT_LIST_DIR})
set(TGON_SOURCE_PATH ${TGON_PATH}/Source)

if (WIN32)
	set(TGON_PLATFORM "WINDOWS")
	set(TGON_GRAPHICS "OPENGL")
elseif (APPLE)
	set(TGON_PLATFORM "MACOS")
	set(TGON_GRAPHICS "OPENGL")
	set(CMAKE_CXX_FLAGS "-x objective-c++")
else ()
	message(FATAL_ERROR "Not supported platform!")
endif ()

# Add sub directories
add_subdirectory(${TGON_SOURCE_PATH})

# Add macros
if (WIN32)
	add_definitions(-DUNICODE -D_UNICODE)
endif ()

add_definitions(-DTGON_PLATFORM_${TGON_PLATFORM}=1 -D${TGON_GRAPHICS}=1)