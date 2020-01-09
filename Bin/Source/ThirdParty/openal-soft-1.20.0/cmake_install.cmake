# Install script for directory: C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/TGON")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Bin/RelWithDebInfo/Debug/OpenAL32.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Bin/RelWithDebInfo/Release/OpenAL32.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Bin/RelWithDebInfo/MinSizeRel/OpenAL32.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Bin/RelWithDebInfo/RelWithDebInfo/OpenAL32.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenAL/OpenALConfig.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenAL/OpenALConfig.cmake"
         "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Bin/Source/ThirdParty/openal-soft-1.20.0/CMakeFiles/Export/lib/cmake/OpenAL/OpenALConfig.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenAL/OpenALConfig-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenAL/OpenALConfig.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenAL" TYPE FILE FILES "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Bin/Source/ThirdParty/openal-soft-1.20.0/CMakeFiles/Export/lib/cmake/OpenAL/OpenALConfig.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenAL" TYPE FILE FILES "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Bin/Source/ThirdParty/openal-soft-1.20.0/CMakeFiles/Export/lib/cmake/OpenAL/OpenALConfig-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenAL" TYPE FILE FILES "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Bin/Source/ThirdParty/openal-soft-1.20.0/CMakeFiles/Export/lib/cmake/OpenAL/OpenALConfig-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenAL" TYPE FILE FILES "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Bin/Source/ThirdParty/openal-soft-1.20.0/CMakeFiles/Export/lib/cmake/OpenAL/OpenALConfig-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/OpenAL" TYPE FILE FILES "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Bin/Source/ThirdParty/openal-soft-1.20.0/CMakeFiles/Export/lib/cmake/OpenAL/OpenALConfig-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/AL" TYPE FILE FILES
    "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/include/AL/al.h"
    "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/include/AL/alc.h"
    "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/include/AL/alext.h"
    "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/include/AL/efx.h"
    "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/include/AL/efx-creative.h"
    "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/include/AL/efx-presets.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Bin/Source/ThirdParty/openal-soft-1.20.0/openal.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openal" TYPE FILE FILES "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/alsoftrc.sample")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openal/hrtf" TYPE FILE FILES
    "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/hrtf/default-44100.mhr"
    "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/hrtf/default-48000.mhr"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openal/presets" TYPE FILE FILES
    "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/presets/3D7.1.ambdec"
    "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/presets/hexagon.ambdec"
    "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/presets/itu5.1.ambdec"
    "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/presets/itu5.1-nocenter.ambdec"
    "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/presets/rectangle.ambdec"
    "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/presets/square.ambdec"
    "C:/Users/ggomdyu/Desktop/프로그래밍/Git/TGON/Source/ThirdParty/openal-soft-1.20.0/presets/presets.txt"
    )
endif()

