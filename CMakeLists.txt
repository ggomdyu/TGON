cmake_minimum_required(VERSION 3.8)

project(TGON)

# Define variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(TGON_PATH ${CMAKE_CURRENT_LIST_DIR})
set(TGON_SOURCE_PATH ${TGON_PATH}/Source)

if (WIN32)
	set(TGON_PLATFORM_NAME "WINDOWS")
	set(TGON_GRAPHICS_NAME "OPENGL")
	set(TGON_UNIX_BASE_OS FALSE)
elseif (APPLE)
	set(TGON_PLATFORM_NAME "MACOS")
	set(TGON_GRAPHICS_NAME "OPENGL")
	set(TGON_UNIX_BASE_OS TRUE)
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

target_compile_definitions(TGON PRIVATE
	TGON_PLATFORM_${TGON_PLATFORM_NAME}=1
	TGON_GRAPHICS_${TGON_GRAPHICS_NAME}=1
)