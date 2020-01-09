cmake_minimum_required (VERSION 3.8)

project(glew)

# Add filters
file(GLOB_RECURSE SRC_PATH_LIST *.c *.cpp *.h)
add_library(glew ${SRC_PATH_LIST})
