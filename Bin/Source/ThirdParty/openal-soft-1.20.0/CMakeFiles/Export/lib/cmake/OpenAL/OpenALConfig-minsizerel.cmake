#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "OpenAL::OpenAL" for configuration "MinSizeRel"
set_property(TARGET OpenAL::OpenAL APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(OpenAL::OpenAL PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/OpenAL32.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS OpenAL::OpenAL )
list(APPEND _IMPORT_CHECK_FILES_FOR_OpenAL::OpenAL "${_IMPORT_PREFIX}/lib/OpenAL32.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
