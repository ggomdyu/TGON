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
#endif

namespace tgon
{

class TGON_API Path
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
//    static constexpr std::string_view GetPathRoot(const std::string_view& path) noexcept;
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
    static bool IsValidDriveChar(char ch) noexcept;
    static bool IsDirectorySeparator(char ch) noexcept;
    static std::string RemoveRelativeSegments(const std::string_view& path);
    static constexpr int32_t GetRootLength(const std::string_view& path) noexcept;
    
/**@section Variable */
public:
    static constexpr char AltDirectorySeparatorChar = '/';
    static constexpr char DirectorySeparatorChar = '\\';
    static constexpr char PathSeparator = ';';
    static constexpr char VolumeSeparatorChar = ':';
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
    auto iterIndex = static_cast<int32_t>(path.length());
    
    while (--iterIndex >= 0)
    {
        if (path[iterIndex] == '.')
        {
            return path.substr(iterIndex);
        }
    }
    
    return std::string_view();
}

constexpr std::string_view Path::GetFileName(const std::string_view& path) noexcept
{
    auto iterIndex = static_cast<int32_t>(path.length());

    while (--iterIndex >= 0)
    {
        if (path[iterIndex] == AltDirectorySeparatorChar || path[iterIndex] == DirectorySeparatorChar)
        {
            return path.substr(iterIndex + 1, path.length() - iterIndex);
        }
    }

    return path;
}

constexpr std::string_view Path::GetFileNameWithoutExtension(const std::string_view& path) noexcept
{
    auto iterIndex = static_cast<int32_t>(path.length());
    auto extensionStartIndex = iterIndex;
    
    while (--iterIndex >= 0)
    {
        if (path[iterIndex] == AltDirectorySeparatorChar || path[iterIndex] == DirectorySeparatorChar)
        {
            return path.substr(iterIndex + 1, extensionStartIndex - (iterIndex + 1));
        }

        if (path[iterIndex] == '.' && path.data()[extensionStartIndex] == '\0')
        {
            extensionStartIndex = iterIndex;
        }
    }

    return std::string_view();
}

constexpr std::string_view Path::GetDirectoryName(const std::string_view& path) noexcept
{
    auto iterIndex = static_cast<int32_t>(path.length());

    while (--iterIndex >= 0)
    {
        if (path[iterIndex] == AltDirectorySeparatorChar || path[iterIndex] == DirectorySeparatorChar)
        {
            return path.substr(0, iterIndex);
        }
    }

    return "";
}

constexpr bool Path::HasExtension(const std::string_view& path) noexcept
{
    auto iterIndex = static_cast<int32_t>(path.length());

    while (--iterIndex >= 0)
    {
        if (path[iterIndex] == '.')
        {
            return (path.length() - (iterIndex + 1)) > 0;
        }
    }
    
    return false;
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

constexpr int32_t Path::GetRootLength(const std::string_view& path) noexcept
{
    return path.length() > 0 && Path::IsDirectorySeparator(path[0]) ? 1 : 0;
}

} /* namespace tgon */
