cmake_minimum_required(VERSION 3.2)

project(icu)

file(GLOB_RECURSE SRC_PATH_LIST source/common/*.c source/common/*.cpp source/common/*.h)
add_library(icu ${SRC_PATH_LIST})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_PATH_LIST})

target_include_directories(icu PUBLIC "include")
