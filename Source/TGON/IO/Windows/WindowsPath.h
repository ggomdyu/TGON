/**
 * @file    WindowsPath.h
 * @author  ggomdyu
 * @since   08/31/2019
 */

#pragma once
#include "Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   undef GetTempPath
#endif

namespace tgon
{

class TGON_API WindowsPath
{
/**@section Constructor */
public:
    WindowsPath() = delete;
    
/**@section Variable */
public:
    static constexpr char DirectorySeparatorChar = '\\';
    static constexpr char AltDirectorySeparatorChar = '/';
    static constexpr char VolumeSeparatorChar = ':';
    static constexpr char PathSeparator = ';';
};

using PlatformPath = WindowsPath;

} /* namespace tgon */
