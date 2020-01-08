cmake_minimum_required (VERSION 3.8)

project(glew)

# Add filters
file(GLOB_RECURSE SRC_PATH_LIST *.c *.cpp *.h)
add_library(glew-2.1.0 STATIC ${SRC_PATH_LIST})

# Add macros
target_compile_definitions(glew-2.1.0 PRIVATE GLEW_STATIC)
