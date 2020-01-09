cmake_minimum_required (VERSION 3.8)

# Add filters
set(GLOB_AGRUMENTS
	*/*.cpp
	*/*.h
	*/*.mm
	CMakeLists.txt
	PrecompiledHeader.h
)
if (APPLE)
	list(APPEND GLOB_AGRUMENTS ${TGON_SOURCE_PATH}/*/*.mm)
endif ()

file(GLOB_RECURSE TEMP_SRC_PATH_LIST ${GLOB_AGRUMENTS})

set(SRC_PATH_LIST)
set(TGON_PLATFORM_NAME_LIST "WINDOWS" "MACOS" "ANDROID" "IOS" "LINUX" "UNIX")
set(TGON_GRAPHICS_NAME_LIST "OPENGL" "VULKAN" "DIRECT3D11" "DIRECT3D12" "METAL")

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

	# Ignore other platform sources
	set(IS_PLATFORM_SPECIFIC_SRC FALSE)
	string(TOUPPER ${SRC_PATH} UPPERCASE_SRC_PATH)
	foreach (PLATFORM_NAME ${TGON_PLATFORM_NAME_LIST})
		string(FIND ${UPPERCASE_SRC_PATH} /${PLATFORM_NAME}/ SUBSTR_INDEX)
		if (NOT SUBSTR_INDEX EQUAL -1)
			set(IS_PLATFORM_SPECIFIC_SRC TRUE)
			if (PLATFORM_NAME STREQUAL TGON_PLATFORM_NAME)
				list(APPEND SRC_PATH_LIST ${SRC_PATH})
				break ()
			elseif (TGON_UNIX_BASE_OS AND PLATFORM_NAME STREQUAL "UNIX")
				list(APPEND SRC_PATH_LIST ${SRC_PATH})
				break ()
			endif()
		endif ()
	endforeach ()

	if (NOT IS_PLATFORM_SPECIFIC_SRC)
		list(APPEND SRC_PATH_LIST ${SRC_PATH})
	endif ()
endforeach ()

foreach (SRC_PATH ${SRC_PATH_LIST})
	message(STATUS ${SRC_PATH})
endforeach ()

add_library(TGON ${SRC_PATH_LIST})
source_group(TREE ${TGON_PATH} FILES ${SRC_PATH_LIST})

# Add include directories
set(TGON_INCLUDE_PATH_LIST
	ThirdParty/gainput-1.0.0/lib/include
	ThirdParty/fmt-6.1.2/include
	ThirdParty/openal-soft-1.20.0
	ThirdParty/openal-soft-1.20.0/alc
	ThirdParty/openal-soft-1.20.0/common
	ThirdParty/openal-soft-1.20.0/include
	ThirdParty/zlib-1.2.11
	ThirdParty/glew-2.1.0/include
	ThirdParty/icu4c-64_2/icu/source/i18n
	ThirdParty/icu4c-64_2/icu/source/common
	ThirdParty/freetype-2.10.1/include
	ThirdParty/GSL-2.0.0/include
	ThirdParty/assimp-4.1.0/include
	ThirdParty/libiconv-1.9.2/include
	ThirdParty/stb
	${CMAKE_CURRENT_SOURCE_DIR}
)

if (WIN32)
	list(APPEND TGON_INCLUDE_PATH_LIST $ENV{DXSDK_DIR}/Include)
endif ()

include_directories(${TGON_INCLUDE_PATH_LIST})
add_subdirectory(ThirdParty/gainput-1.0.0)
add_subdirectory(ThirdParty/glew-2.1.0)
add_subdirectory(ThirdParty/freetype-2.10.1)

# Set properties
set_target_properties(gainput PROPERTIES FOLDER "ThirdParty")
set_target_properties(glew PROPERTIES FOLDER "ThirdParty")
set_target_properties(freetype PROPERTIES FOLDER "ThirdParty")

# Add macros
target_compile_definitions(glew PUBLIC GLEW_STATIC)
target_compile_definitions(freetype PUBLIC
    FT_DEBUG_LEVEL_ERROR
	FT_DEBUG_LEVEL_TRACE
	FT2_BUILD_LIBRARY
)
target_link_libraries(TGON
    PRIVATE glew freetype
)

target_compile_definitions(TGON PRIVATE
	U_STATIC_IMPLEMENTATION
	U_COMMON_IMPLEMENTATION
	U_I18N_IMPLEMENTATION
	AL_BUILD_LIBRARY
	AL_ALEXT_PROTOTYPES
	OpenAL_EXPORTS
)
