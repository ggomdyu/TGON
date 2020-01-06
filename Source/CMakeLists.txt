cmake_minimum_required (VERSION 3.8)

file (GLOB_RECURSE SRC_TGON
	"${TGON_SOURCE_PATH}/*/*.cpp"
	"${TGON_SOURCE_PATH}/*/*.h"
	"${TGON_SOURCE_PATH}/PrecompiledHeader.h"
)

add_library(TGON ${SRC_TGON})
source_group(TREE ${TGON_PATH} FILES ${SRC_TGON})