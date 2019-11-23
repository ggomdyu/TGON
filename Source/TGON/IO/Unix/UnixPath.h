/**
 * @file    UnixPath.h
 * @author  ggomdyu
 * @since   10/30/2019
 */

#pragma once
#include "Platform/Config.h"

namespace tgon
{

class UnixPath
{
/**@section Constructor */
public:
    UnixPath() = delete;
    
/**@section Variable */
public:
    static constexpr char DirectorySeparatorChar = '/';
    static constexpr char AltDirectorySeparatorChar = '/';
    static constexpr char VolumeSeparatorChar = '/';
    static constexpr char PathSeparator = ':';
};

using PlatformPath = UnixPath;

} /* namespace tgon */
