cmake_minimum_required (VERSION 3.8)

# Add include directories
set(TGON_INCLUDE_PATH_LIST
	gainput-1.0.0/lib/include
	fmt-6.1.2/include
	openal-soft-1.20.0
	openal-soft-1.20.0/alc
	openal-soft-1.20.0/common
	openal-soft-1.20.0/include
	zlib-1.2.11
	glew-2.1.0/include
	icu4c-64_2/icu/source/i18n
	icu4c-64_2/icu/source/common
	freetype-2.10.1/include
	GSL-2.0.0/include
	assimp-4.1.0/include
	libiconv-1.9.2/include
	stb
)

if (WIN32)
	list(APPEND TGON_INCLUDE_PATH_LIST $ENV{DXSDK_DIR}/Include)
endif ()

include_directories(${TGON_INCLUDE_PATH_LIST})
add_subdirectory(gainput-1.0.0)
add_subdirectory(glew-2.1.0)
add_subdirectory(freetype-2.10.1)

set_target_properties(gainputstatic PROPERTIES FOLDER "ThirdParty")
set_target_properties(glew PROPERTIES FOLDER "ThirdParty")
set_target_properties(freetype PROPERTIES FOLDER "ThirdParty")

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