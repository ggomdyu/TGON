cmake_minimum_required (VERSION 3.8)

# Add filters
file(GLOB_RECURSE SRC_LIST_TEMP
	${TGON_SOURCE_PATH}/*/*.cpp
	${TGON_SOURCE_PATH}/*/*.h
	${TGON_SOURCE_PATH}/PrecompiledHeader.h
)

set(SRC_LIST)
set(TGON_PLATFORM_LIST "WINDOWS" "MACOS" "ANDROID" "IOS" "LINUX" "UNIX")
set(TGON_GRAPHICS_LIST "OPENGL" "VULKAN" "DIRECT3D11" "DIRECT3D12" "METAL")

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
	foreach (ITER_GRAPHICS ${TGON_GRAPHICS_LIST})
		string(FIND ${SRC} /${ITER_GRAPHICS}/ SUBSTR_INDEX)
		message(STATUS ${SRC})
		if (NOT SUBSTR_INDEX EQUAL -1)
			set(NEED_TO_CONTINUE TRUE)
			if (ITER_GRAPHICS STREQUAL TGON_GRAPHICS)
				set(NEED_TO_CONTINUE FALSE)
				break ()
			endif ()
		endif ()
	endforeach ()

	if (NEED_TO_CONTINUE)
		continue ()
	endif ()

	# Ignore other platform sources
	foreach (ITER_PLATFORM ${TGON_PLATFORM_LIST})
		string(FIND ${SRC} /${ITER_PLATFORM}/ SUBSTR_INDEX)
		if (NOT SUBSTR_INDEX EQUAL -1)
			set(NEED_TO_CONTINUE TRUE)
			if (ITER_PLATFORM STREQUAL TGON_PLATFORM)
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