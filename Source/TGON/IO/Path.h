/**
 * @file    Path.h
 * @author  ggomdyu
 * @since   04/07/2017
 */

#pragma once
#include <cstdint>
#include <string>
#include <optional>
#include <gsl/span>

#include "Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsPath.h"
#elif TGON_PLATFORM_MACOS
#   include "Unix/UnixPath.h"
#endif

namespace tgon
{

class TGON_API Path :
    private PlatformPath
{
/**@section Constructor */
public:
    Path() = delete;
    
/**@section Method */
public:
    static std::string Combine(const std::string_view& path1, const std::string_view& path2);
    static int32_t Combine(const std::string_view& path1, const std::string_view& path2, char* destStr, int32_t destStrBufferLen);
    template <int32_t Length>
    static int32_t Combine(const std::string_view& path1, const std::string_view& path2, const gsl::span<char, Length>& destStr);
    static constexpr bool IsPathRooted(const std::string_view& path) noexcept;
    static constexpr std::string_view GetExtension(const std::string_view& path) noexcept;
    static constexpr std::string_view GetFileName(const std::string_view& path) noexcept;
    static constexpr std::string_view GetFileNameWithoutExtension(const std::string_view& path) noexcept;
    static constexpr std::string_view GetDirectoryName(const std::string_view& path) noexcept;
    static constexpr bool HasExtension(const std::string_view& path) noexcept;
    static std::string ChangeExtension(const std::string_view& path, const std::string_view& extension);
    static int32_t ChangeExtension(const std::string_view& path, const std::string_view& extension, char* destStr, int32_t destStrBufferLen);
    static std::string GetFullPath(const std::string_view& path);
    static std::string GetFullPath(const std::string_view& path, const std::string_view& basePath);
    static constexpr std::string_view GetPathRoot(const std::string_view& path) noexcept;
    static int32_t GetRandomFileName(char* destStr, int32_t destStrBufferLen);
    template <int32_t Length>
    static int32_t GetRandomFileName(const gsl::span<char, Length>& destStr);
    static std::string GetRandomFileName();
    static std::string GetTempPath();
    static int32_t GetTempPath(char* destStr, int32_t destStrBufferLen);
    template <int32_t Length>
    static int32_t GetTempPath(const gsl::span<char, Length>& destStr);
    static gsl::span<const char> GetInvalidFileNameChars() noexcept;
    static gsl::span<const char> GetInvalidPathChars() noexcept;

private:
    static constexpr bool IsValidDriveChar(char ch) noexcept;
    static constexpr bool IsDirectorySeparator(char ch) noexcept;
    static std::string RemoveRelativeSegments(const std::string_view& path);
    static constexpr int32_t GetRootLength(const std::string_view& path) noexcept;
    
/**@section Variable */
public:
    static constexpr char AltDirectorySeparatorChar = PlatformPath::AltDirectorySeparatorChar;
    static constexpr char DirectorySeparatorChar = PlatformPath::DirectorySeparatorChar;
    static constexpr char PathSeparator = PlatformPath::PathSeparator;
    static constexpr char VolumeSeparatorChar = PlatformPath::VolumeSeparatorChar;
    
private:
    static constexpr char AltDirectorySeparatorStr[] = {AltDirectorySeparatorChar, '\0'};
    static constexpr char DirectorySeparatorStr[] = {DirectorySeparatorChar, '\0'};
};

template <int32_t Length>
inline int32_t Path::Combine(const std::string_view& path1, const std::string_view& path2, const gsl::span<char, Length>& destStr)
{
    return Combine(path1, path2, &destStr[0], Length);
}

constexpr bool Path::IsPathRooted(const std::string_view& path) noexcept
{
    return (path.length() >= 1 && IsDirectorySeparator(path[0])) || (path.length() >= 2 && IsValidDriveChar(path[0]) && path[1] == VolumeSeparatorChar);
}

constexpr std::string_view Path::GetExtension(const std::string_view& path) noexcept
{
    auto iterIndex = path.length();
    while (iterIndex > 0)
    {
        --iterIndex;
        
        if (path[iterIndex] == '.')
        {
            return path.substr(iterIndex);
        }
    }
    
    return {};
}

constexpr std::string_view Path::GetFileName(const std::string_view& path) noexcept
{
    auto iterIndex = path.length();
    while (iterIndex > 0)
    {
        --iterIndex;
        
        if (path[iterIndex] == AltDirectorySeparatorChar || path[iterIndex] == DirectorySeparatorChar)
        {
            return path.substr(iterIndex + 1, path.length() - iterIndex);
        }
    }

    return path;
}

constexpr std::string_view Path::GetFileNameWithoutExtension(const std::string_view& path) noexcept
{
    auto extensionStartIndex = path.length();
    
    auto iterIndex = extensionStartIndex;
    while (iterIndex > 0)
    {
        --iterIndex;
        
        if (IsDirectorySeparator(path[iterIndex]))
        {
            return path.substr(iterIndex + 1, extensionStartIndex - (iterIndex + 1));
        }
        else if (iterIndex == 0)
        {
            return path.substr(0, extensionStartIndex);
        }

        if (path[iterIndex] == '.' && (extensionStartIndex == path.length()))
        {
            extensionStartIndex = iterIndex;
        }
    }

    return path;
}

constexpr std::string_view Path::GetDirectoryName(const std::string_view& path) noexcept
{
    auto iterIndex = path.length();
    while (iterIndex > 0)
    {
        --iterIndex;
        
        if (path[iterIndex] == AltDirectorySeparatorChar || path[iterIndex] == DirectorySeparatorChar)
        {
            return path.substr(0, iterIndex);
        }
    }

    return {};
}

constexpr bool Path::HasExtension(const std::string_view& path) noexcept
{
    auto iterIndex = path.length();
    while (iterIndex > 0)
    {
        --iterIndex;
        
        if (path[iterIndex] == '.')
        {
            return path.length() > (iterIndex + 1);
        }
    }
    
    return false;
}

constexpr std::string_view Path::GetPathRoot(const std::string_view& path) noexcept
{
    // UNIX
    if constexpr (DirectorySeparatorChar == '/')
    {
        return IsDirectorySeparator(path[0]) ? DirectorySeparatorStr : std::string_view();
    }
//    // Windows
//    else
//    {
//        int len = 2;
//
//        if (path.Length == 1 && IsDirectorySeparator (path [0]))
//            return DirectorySeparatorStr;
//        else if (path.Length < 2)
//            return String.Empty;
//
//        if (IsDirectorySeparator (path [0]) && IsDirectorySeparator (path[1])) {
//            // UNC: \\server or \\server\share
//            // Get server
//            while (len < path.Length && !IsDirectorySeparator (path [len])) len++;
//
//            // Get share
//            if (len < path.Length) {
//                len++;
//                while (len < path.Length && !IsDirectorySeparator (path [len])) len++;
//            }
//
//            return DirectorySeparatorStr +
//                DirectorySeparatorStr +
//                path.Substring (2, len - 2).Replace (AltDirectorySeparatorChar, DirectorySeparatorChar);
//        } else if (IsDirectorySeparator (path [0])) {
//            // path starts with '\' or '/'
//            return DirectorySeparatorStr;
//        } else if (path[1] == VolumeSeparatorChar) {
//            // C:\folder
//            if (path.Length >= 3 && (IsDirectorySeparator (path [2]))) len++;
//        } else
//            return Directory.GetCurrentDirectory ().Substring (0, 2);// + path.Substring (0, len);
//        return path.Substring (0, len);
//    }
    return "";
}

template <int32_t Length>
inline int32_t Path::GetRandomFileName(const gsl::span<char, Length>& destStr)
{
    return GetRandomFileName(&destStr[0], Length);
}

template <int32_t Length>
inline int32_t Path::GetTempPath(const gsl::span<char, Length>& destStr)
{
    return GetTempPath(&destStr[0], Length);
}

constexpr bool Path::IsDirectorySeparator(char ch) noexcept
{
    return ch == AltDirectorySeparatorChar || ch == DirectorySeparatorChar;
}

constexpr bool Path::IsValidDriveChar(char ch) noexcept
{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

constexpr int32_t Path::GetRootLength(const std::string_view& path) noexcept
{
    return path.length() > 0 && Path::IsDirectorySeparator(path[0]) ? 1 : 0;
}

} /* namespace tgon */
