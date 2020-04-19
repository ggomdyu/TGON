#pragma once

namespace tg
{

class WindowsPath
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

}