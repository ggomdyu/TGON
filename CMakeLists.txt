cmake_minimum_required(VERSION 3.8)

project(TGON)

# Define variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(TGON_PATH ${CMAKE_CURRENT_LIST_DIR})
set(TGON_SOURCE_PATH ${TGON_PATH}/Source)

option(TGON_GRAPHICS_OPENGL "Build with OpenGL Graphics API." ON)
if (WIN32)
	set(TGON_PLATFORM "TGON_PLATFORM_WINDOWS")
	set(TGON_GRAPHICS "TGON_GRAPHICS_OPENGL")
	set(TGON_PLATFORM_PREFIX "Windows")
	set(TGON_GRAPHICS_PREFIX "OpenGL")
	option(TGON_GRAPHICS_DIRECT3D11 "Build with Direct3D11 Graphics API." OFF)
	add_definitions(-DUNICODE -D_UNICODE)
elseif (APPLE)
	set(TGON_PLATFORM "TGON_PLATFORM_MACOS")
	set(TGON_GRAPHICS "TGON_GRAPHICS_OPENGL")
	set(TGON_PLATFORM_PREFIX "MacOS")
	set(TGON_GRAPHICS_PREFIX "OpenGL")
else ()
	message(FATAL_ERROR "Not supported platform!")
endif ()

add_subdirectory(${TGON_SOURCE_PATH})

# Add macros
target_compile_definitions(TGON PRIVATE
	${TGON_PLATFORM}=1
	${TGON_GRAPHICS}=1
)