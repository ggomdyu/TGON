cmake_minimum_required(VERSION 3.8)

function(init_thirdparty_subdirectories)
    option(ALSOFT_TESTS "" FALSE)
    option(ALSOFT_UTILS "" FALSE)
    option(ALSOFT_EXAMPLES "" FALSE)
    set(LIBTYPE "STATIC")
    add_subdirectory(ThirdParty/openal-soft-1.20.1)

    option(GAINPUT_TESTS "" FALSE)
    option(GAINPUT_BUILD_SHARED "" FALSE)
    option(GAINPUT_SAMPLES "" FALSE)
    add_subdirectory(ThirdParty/gainput-1.0.0)

    add_subdirectory(ThirdParty/fmt-6.1.2)
    add_subdirectory(ThirdParty/freetype-2.10.1)
    add_subdirectory(ThirdParty/glew-2.1.0)
    add_subdirectory(ThirdParty/icu4c-64_2/icu)
    add_subdirectory(ThirdParty/zlib-1.2.11)
endfunction()

function(init_thirdparty_properties)
    target_compile_definitions(freetype PUBLIC FT_DEBUG_LEVEL_ERROR FT_DEBUG_LEVEL_TRACE FT2_BUILD_LIBRARY)
    target_compile_definitions(glew PUBLIC GLEW_STATIC)
    target_compile_definitions(icu PUBLIC U_STATIC_IMPLEMENTATION U_COMMON_IMPLEMENTATION U_I18N_IMPLEMENTATION)
    target_compile_definitions(OpenAL PUBLIC AL_LIBTYPE_STATIC)
    target_compile_definitions(common PUBLIC AL_LIBTYPE_STATIC)

    set_target_properties(common PROPERTIES FOLDER ThirdParty)
    set_target_properties(ex-common PROPERTIES FOLDER ThirdParty)
    set_target_properties(fmt PROPERTIES FOLDER ThirdParty)
    set_target_properties(freetype PROPERTIES FOLDER ThirdParty)
    set_target_properties(gainputstatic PROPERTIES FOLDER ThirdParty)
    set_target_properties(glew PROPERTIES FOLDER ThirdParty)
    set_target_properties(icu PROPERTIES FOLDER ThirdParty)
    set_target_properties(native-tools PROPERTIES FOLDER ThirdParty)
    set_target_properties(OpenAL PROPERTIES FOLDER ThirdParty)
    set_target_properties(zlib PROPERTIES FOLDER ThirdParty)
endfunction()

function(init_tgon_subdirectories)
    set(GLOB_AGRUMENTS *.cpp *c *.h)

    if(APPLE)
        list(APPEND GLOB_AGRUMENTS ${TGON_SOURCE_PATH}/*/*.mm)
    endif()

    file(GLOB_RECURSE TEMP_SRC_PATH_LIST ${GLOB_AGRUMENTS})

    set(SRC_PATH_LIST)
    set(TGON_PLATFORM_NAME_LIST "WINDOWS" "MACOS" "ANDROID" "IOS" "LINUX" "UNIX")
    set(TGON_GRAPHICS_NAME_LIST "OPENGL" "VULKAN" "DIRECT3D11" "DIRECT3D12" "METAL")

    foreach(SRC_PATH ${TEMP_SRC_PATH_LIST})
        # Ignore third-party directories
        string(FIND ${SRC_PATH} "/ThirdParty/" SUBSTR_INDEX)
        if(NOT SUBSTR_INDEX EQUAL -1)
            continue()
        endif()

        # Ignore legacy directories
        string(FIND ${SRC_PATH} "/Legacy/" SUBSTR_INDEX)
        if(NOT SUBSTR_INDEX EQUAL -1)
            continue()
        endif()

        # Ignore legacy directories
        string(FIND ${SRC_PATH} "/Test/" SUBSTR_INDEX)
        if(NOT SUBSTR_INDEX EQUAL -1)
            continue()
        endif()

        # Ignore other platform sources
        set(IS_PLATFORM_SPECIFIC_SRC FALSE)
        set(IS_PLATFORM_MATCHED_SRC FALSE)
        string(TOUPPER ${SRC_PATH} UPPERCASE_SRC_PATH)
        foreach(PLATFORM_NAME ${TGON_PLATFORM_NAME_LIST})
            string(FIND ${UPPERCASE_SRC_PATH} /${PLATFORM_NAME}/ SUBSTR_INDEX)
            if(NOT SUBSTR_INDEX EQUAL -1)
                set(IS_PLATFORM_SPECIFIC_SRC TRUE)
                if(PLATFORM_NAME STREQUAL TGON_PLATFORM_NAME)
                    set(IS_PLATFORM_MATCHED_SRC TRUE)
                    break()
                elseif(TGON_UNIX_BASE_OS AND PLATFORM_NAME STREQUAL "UNIX")
                    set(IS_PLATFORM_MATCHED_SRC TRUE)
                    break()
                endif()
            endif()
        endforeach()

        if(IS_PLATFORM_SPECIFIC_SRC AND NOT IS_PLATFORM_MATCHED_SRC)
            continue()
        endif()

        # Ignore other graphics API sources
        string(FIND ${SRC_PATH} "TGON/Source/Graphics/" SUBSTR_INDEX)
        if(NOT SUBSTR_INDEX EQUAL -1)
            set(IS_GRAPHICS_SPECIFIC_SRC FALSE)
            set(IS_GRAPHICS_MATCHED_SRC FALSE)
            string(TOUPPER ${SRC_PATH} UPPERCASE_SRC_PATH)
            foreach(GRAPHICS_NAME ${TGON_GRAPHICS_NAME_LIST})
                string(FIND ${UPPERCASE_SRC_PATH} /${GRAPHICS_NAME}/ SUBSTR_INDEX)
                if(NOT SUBSTR_INDEX EQUAL -1)
                    set(IS_GRAPHICS_SPECIFIC_SRC TRUE)
                    if(GRAPHICS_NAME STREQUAL TGON_GRAPHICS_NAME)
                        set(IS_GRAPHICS_MATCHED_SRC TRUE)
                        break()
                    endif()
                endif()
            endforeach()

            if(IS_GRAPHICS_SPECIFIC_SRC AND NOT IS_GRAPHICS_MATCHED_SRC)
                continue()
            endif()
        endif()

        list(APPEND SRC_PATH_LIST ${SRC_PATH})
    endforeach()

    add_library(TGON ${SRC_PATH_LIST})
    source_group(TREE ${TGON_PATH} FILES ${SRC_PATH_LIST})
endfunction()

function(init_tgon_properties)
    set(TGON_INCLUDE_PATH_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}
        ThirdParty/assimp-4.1.0/include
        ThirdParty/fmt-6.1.2/include
        ThirdParty/gainput-1.0.0/lib/include
        ThirdParty/GSL-2.0.0/include
        ThirdParty/icu4c-64_2/icu/source/common
        ThirdParty/icu4c-64_2/icu/source/i18n
        ThirdParty/libiconv-1.9.2/include
        ThirdParty/openal-soft-1.20.1
        ThirdParty/openal-soft-1.20.1/alc
        ThirdParty/openal-soft-1.20.1/common
        ThirdParty/openal-soft-1.20.1/include
        ThirdParty/stb
        ThirdParty/zlib-1.2.11
    )

    if(WIN32)
        list(APPEND TGON_INCLUDE_PATH_LIST $ENV{DXSDK_DIR}/Include)
    endif()

    set_target_properties(TGON PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO FOLDER TGON)

    target_include_directories(TGON PUBLIC ${TGON_INCLUDE_PATH_LIST})
    target_link_libraries(TGON PUBLIC comcon fmt freetype gainputstatic glew icu OpenAL)

    target_compile_definitions(TGON PUBLIC TGON_PLATFORM_${TGON_PLATFORM_NAME}=1 TGON_GRAPHICS_${TGON_GRAPHICS_NAME}=1)
    if(MSVC)
        target_compile_options(TGON PRIVATE /YcPrecompiledHeader.h /Oi $<$<CONFIG:Debug>:/Zi> $<$<CONFIG:Release>:>)
    endif()
endfunction()

init_thirdparty_subdirectories()
init_thirdparty_properties()

init_tgon_subdirectories()
init_tgon_properties()
