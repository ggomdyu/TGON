cmake_minimum_required (VERSION 3.8)

# Add filters
set(GLOB_AGRUMENTS
	${TGON_SOURCE_PATH}/*/*.cpp
	${TGON_SOURCE_PATH}/*/*.h
	${TGON_SOURCE_PATH}/PrecompiledHeader.h
	${TGON_SOURCE_PATH}/*/*.mm
)
if (APPLE)
	list(APPEND GLOB_AGRUMENTS ${TGON_SOURCE_PATH}/*/*.mm)
endif ()

file(GLOB_RECURSE TEMP_SRC_PATH_LIST ${GLOB_AGRUMENTS})

set(SRC_PATH_LIST)
set(TGON_PLATFORM_NAME_LIST "WINDOWS" "MACOS" "ANDROID" "IOS" "LINUX" "UNIX")
set(TGON_GRAPHICS_NAME_LIST "OPENGL" "VULKAN" "DIRECT3D11" "DIRECT3D12" "METAL")

function(is_platform_src SRC_PATH IS_PLATFORM_SRC)
	set(IS_PLATFORM_SRC FALSE)
	get_filename_component(FILE_NAME ${SRC_PATH} NAME)
	string(TOUPPER ${FILE_NAME} UPPERCASE_FILE_NAME)
	foreach (PLATFORM_NAME ${TGON_PLATFORM_NAME_LIST})
		string(FIND ${UPPERCASE_FILE_NAME} ${PLATFORM_NAME} SUBSTR_INDEX)
		if (SUBSTR_INDEX EQUAL 0)
			if (PLATFORM_NAME STREQUAL TGON_PLATFORM_NAME)
				set(IS_PLATFORM_SRC TRUE)
				break ()
			endif ()
		endif ()
	endforeach ()
endfunction()

foreach (SRC_PATH ${TEMP_SRC_PATH_LIST})
	# Ignore third-party libraries
	string(FIND ${SRC_PATH} "TGON/Source/ThirdParty/" SUBSTR_INDEX)
	if (NOT SUBSTR_INDEX EQUAL -1)
		continue ()
	endif ()

	# Ignore other graphics API sources
	string(TOUPPER ${SRC_PATH} UPPERCASE_SRC)
	string(FIND ${SRC_PATH} "TGON/Source/Graphics/" SUBSTR_INDEX)
	if (NOT SUBSTR_INDEX EQUAL -1)
		string(FIND ${UPPERCASE_SRC} "/${TGON_GRAPHICS_NAME}/" SUBSTR_INDEX)
		if (SUBSTR_INDEX EQUAL -1)
			continue ()
		endif ()
	endif ()

	message("${SRC_PATH}")

	#set(IS_PLATFORM_SRC FALSE)
	#is_platform_src(${SRC} IS_PLATFORM_SRC)
	#if (IS_PLATFORM_SRC)
	#endif()
	
	#set(NEED_TO_CONTINUE FALSE)
	#foreach (ITER_GRAPHICS ${TGON_GRAPHICS_NAME_LIST})
	#	string(FIND ${UPPERCASE_SRC} /${ITER_GRAPHICS}/ SUBSTR_INDEX)
	#	if (NOT SUBSTR_INDEX EQUAL -1)
	#		set(NEED_TO_CONTINUE TRUE)
	#		if (ITER_GRAPHICS STREQUAL TGON_GRAPHICS)
	#			set(NEED_TO_CONTINUE FALSE)
	#			break ()
	#		endif ()
	#	endif ()
	#endforeach ()
	#
	#if (NEED_TO_CONTINUE)
	#	continue ()
	#endif ()
	#
	## Ignore other platform sources
	#foreach (ITER_PLATFORM ${TGON_PLATFORM_NAME_LIST})
	#	string(FIND ${UPPERCASE_SRC} /${ITER_PLATFORM}/ SUBSTR_INDEX)
	#	if (NOT SUBSTR_INDEX EQUAL -1)
	#		set(NEED_TO_CONTINUE TRUE)
	#		if (ITER_PLATFORM STREQUAL TGON_PLATFORM_NAME)
	#			list(APPEND SRC_PATH_LIST ${SRC})
	#			break ()
	#		endif ()
	#	endif ()
	#endforeach ()
	#
	#if (NEED_TO_CONTINUE)
	#	continue ()
	#endif ()
	
	list(APPEND SRC_PATH_LIST ${SRC})
endforeach ()


foreach (SRC ${SRC_PATH_LIST})
#	message(STATUS ${SRC})
endforeach ()

add_library(TGON ${SRC_PATH_LIST})
source_group(TREE ${TGON_PATH} FILES ${SRC_PATH_LIST})

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