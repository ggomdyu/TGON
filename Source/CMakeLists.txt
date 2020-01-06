cmake_minimum_required (VERSION 3.8)

# Add filters
file(GLOB_RECURSE SRC_LIST_TEMP
	${TGON_SOURCE_PATH}/*/*.cpp
	${TGON_SOURCE_PATH}/*/*.h
	${TGON_SOURCE_PATH}/PrecompiledHeader.h
)

set(SRC_LIST)
set(TGON_PLATFORM_PREFIXES "Windows" "MacOS" "Android" "IOS" "Linux" "Unix")
set(TGON_GRAPHICS_PREFIXES "OpenGL" "Vulkan" "Direct3D11" "Direct3D12" "Metal")

message (STATUS ${SRC})

foreach (SRC ${SRC_LIST_TEMP})
	set(SUBSTR_INDEX 0)

	# Ignore third-party libraries
	string(FIND ${SRC} "TGON/Source/ThirdParty/" SUBSTR_INDEX)
	if (NOT SUBSTR_INDEX EQUAL -1)
		continue ()
	endif ()

	# Ignore other graphics API sources
	set(NEED_TO_CONTINUE FALSE)
	foreach (GRAPHICS_PREFIX ${TGON_GRAPHICS_PREFIXES})
		string(FIND ${SRC} /${GRAPHICS_PREFIX}/ SUBSTR_INDEX)
		if (NOT SUBSTR_INDEX EQUAL -1)
			set(NEED_TO_CONTINUE TRUE)
			if (GRAPHICS_PREFIX STREQUAL TGON_GRAPHICS_PREFIX)
				list(APPEND SRC_LIST ${SRC})
				break ()
			endif ()
		endif ()
	endforeach ()

	if (NEED_TO_CONTINUE)
		continue ()
	endif ()

	# Ignore other platform sources
	foreach (PLATFORM_PREFIX ${TGON_PLATFORM_PREFIXES})
		string(FIND ${SRC} /${PLATFORM_PREFIX}/ SUBSTR_INDEX)
		if (NOT SUBSTR_INDEX EQUAL -1)
			set(NEED_TO_CONTINUE TRUE)
			if (PLATFORM_PREFIX STREQUAL TGON_PLATFORM_PREFIX)
				list(APPEND SRC_LIST ${SRC})
				break ()
			endif ()
		endif ()
	endforeach ()
	
	if (NEED_TO_CONTINUE)
		continue ()
	endif ()
	
	list(APPEND SRC_LIST ${SRC})
endforeach ()


foreach (SRC ${SRC_LIST})
	message(STATUS ${SRC})
endforeach ()

add_library(TGON ${SRC_LIST})
source_group(TREE ${TGON_PATH} FILES ${SRC_LIST})

# Add include directories
set(TGON_THIRDPARTY_PATH ${TGON_SOURCE_PATH}/ThirdParty)
set(TGON_THIRDPARTY_DIRECTORIES
	${TGON_THIRDPARTY_PATH}/gainput-1.0.0/lib/include
	${TGON_THIRDPARTY_PATH}/fmt-6.1.2/include
	${TGON_THIRDPARTY_PATH}/openal-soft-1.20.0
	${TGON_THIRDPARTY_PATH}/openal-soft-1.20.0/alc
	${TGON_THIRDPARTY_PATH}/openal-soft-1.20.0/common
	${TGON_THIRDPARTY_PATH}/openal-soft-1.20.0/include
	${TGON_THIRDPARTY_PATH}/zlib-1.2.11
	${TGON_THIRDPARTY_PATH}/glew-2.1.0/include
	${TGON_THIRDPARTY_PATH}/icu4c-64_2/icu/source/i18n
	${TGON_THIRDPARTY_PATH}/icu4c-64_2/icu/source/common
	${TGON_THIRDPARTY_PATH}/freetype-2.10.0/include
	${TGON_THIRDPARTY_PATH}/GSL-2.0.0/include
	${TGON_THIRDPARTY_PATH}/assimp-4.1.0/include
	${TGON_THIRDPARTY_PATH}/libiconv-1.9.2/include
	${TGON_THIRDPARTY_PATH}/stb
)

if (WIN32)
	list(APPEND TGON_THIRDPARTY_DIRECTORIES $ENV{DXSDK_DIR}/Include)
endif ()

include_directories(${TGON_SOURCE_PATH})
include_directories(${TGON_THIRDPARTY_DIRECTORIES})

set(GAINPUT_TESTS OFF)

# Add macros
target_compile_definitions(TGON PRIVATE
	GLEW_STATIC
	FT_DEBUG_LEVEL_ERROR
	FT_DEBUG_LEVEL_TRACE
	FT2_BUILD_LIBRARY
	U_STATIC_IMPLEMENTATION
	U_COMMON_IMPLEMENTATION
	U_I18N_IMPLEMENTATION
	AL_BUILD_LIBRARY
	AL_ALEXT_PROTOTYPES
	OpenAL_EXPORTS
)