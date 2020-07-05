#pragma once

#include <cstdint>
#include <string>
#include <span>

#if TGON_PLATFORM_WINDOWS
#include "Windows/WindowsPath.h"
#elif TGON_SUPPORT_POSIX
#include "Posix/PosixPath.h"
#endif

namespace tg
{

class Path :
    private PlatformPath
{
/**@section Constructor */
public:
    Path() = delete;
    
/**@section Method */
public:
    static std::u8string Combine(const std::u8string_view& path1, const std::u8string_view& path2);
    static int32_t Combine(const std::u8string_view& path1, const std::u8string_view& path2, char8_t* destStr, int32_t destStrBufferLen);
    template <int32_t _Length>
    static int32_t Combine(const std::u8string_view& path1, const std::u8string_view& path2, const std::span<char8_t, _Length>& destStr);
    static constexpr bool IsPathRooted(const std::u8string_view& path) noexcept;
    static constexpr std::u8string_view GetExtension(const std::u8string_view& path) noexcept;
    static constexpr std::u8string_view GetFileName(const std::u8string_view& path) noexcept;
    static constexpr std::u8string_view GetFileNameWithoutExtension(const std::u8string_view& path) noexcept;
    static constexpr std::u8string_view GetDirectoryName(const std::u8string_view& path) noexcept;
    static constexpr bool HasExtension(const std::u8string_view& path) noexcept;
    static std::u8string ChangeExtension(const std::u8string_view& path, const std::u8string_view& extension);
    static int32_t ChangeExtension(const std::u8string_view& path, const std::u8string_view& extension, char8_t* destStr, int32_t destStrBufferLen);
    static std::u8string GetFullPath(const std::u8string_view& path);
    static std::u8string GetFullPath(const std::u8string_view& path, const std::u8string_view& basePath);
    static constexpr std::u8string_view GetPathRoot(const std::u8string_view& path) noexcept;
    static int32_t GetRandomFileName(char8_t* destStr, int32_t destStrBufferLen);
    template <int32_t _Length>
    static int32_t GetRandomFileName(const std::span<char8_t, _Length>& destStr);
    static std::u8string GetRandomFileName();
    static std::u8string GetTempPath();
    static int32_t GetTempPath(char8_t* destStr, int32_t destStrBufferLen);
    template <int32_t _Length>
    static int32_t GetTempPath(const std::span<char8_t, _Length>& destStr);
    static std::span<const char8_t> GetInvalidFileNameChars() noexcept;
    static std::span<const char8_t> GetInvalidPathChars() noexcept;
    static constexpr int32_t GetRootLength(const std::u8string_view& path) noexcept;
    static constexpr bool IsDirectorySeparator(char8_t ch) noexcept;
    
private:
    static constexpr bool IsValidDriveChar(char8_t ch) noexcept;
    static std::u8string RemoveRelativeSegments(const std::u8string_view& path);
    
/**@section Variable */
public:
    static constexpr char8_t AltDirectorySeparatorChar = PlatformPath::AltDirectorySeparatorChar;
    static constexpr char8_t DirectorySeparatorChar = PlatformPath::DirectorySeparatorChar;
    static constexpr char8_t PathSeparator = PlatformPath::PathSeparator;
    static constexpr char8_t VolumeSeparatorChar = PlatformPath::VolumeSeparatorChar;
    
private:
    static constexpr char8_t AltDirectorySeparatorStr[] = {AltDirectorySeparatorChar, '\0'};
    static constexpr char8_t DirectorySeparatorStr[] = {DirectorySeparatorChar, '\0'};
};

template <int32_t _Length>
int32_t Path::Combine(const std::u8string_view& path1, const std::u8string_view& path2, const std::span<char8_t, _Length>& destStr)
{
    return Combine(path1, path2, &destStr[0], _Length);
}

constexpr bool Path::IsPathRooted(const std::u8string_view& path) noexcept
{
    return (path.length() >= 1 && IsDirectorySeparator(path[0])) || (path.length() >= 2 && IsValidDriveChar(path[0]) && path[1] == VolumeSeparatorChar);
}

constexpr std::u8string_view Path::GetExtension(const std::u8string_view& path) noexcept
{
    auto iterIndex = path.length();
    while (iterIndex-- > 0)
    {
        if (path[iterIndex] == '.')
        {
            return path.substr(iterIndex);
        }
    }
    
    return {};
}

constexpr std::u8string_view Path::GetFileName(const std::u8string_view& path) noexcept
{
    auto iterIndex = path.length();
    while (iterIndex-- > 0)
    {
        if (path[iterIndex] == AltDirectorySeparatorChar || path[iterIndex] == DirectorySeparatorChar)
        {
            return path.substr(iterIndex + 1, path.length() - iterIndex);
        }
    }

    return path;
}

constexpr std::u8string_view Path::GetFileNameWithoutExtension(const std::u8string_view& path) noexcept
{
    auto extensionStartIndex = path.length();
    
    auto iterIndex = extensionStartIndex;
    while (iterIndex-- > 0)
    {
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

constexpr std::u8string_view Path::GetDirectoryName(const std::u8string_view& path) noexcept
{
    auto iterIndex = path.length();
    while (iterIndex-- > 0)
    {
        if (path[iterIndex] == AltDirectorySeparatorChar || path[iterIndex] == DirectorySeparatorChar)
        {
            return path.substr(0, iterIndex);
        }
    }

    return {};
}

constexpr bool Path::HasExtension(const std::u8string_view& path) noexcept
{
    auto iterIndex = path.length();
    while (iterIndex-- > 0)
    {
        if (path[iterIndex] == '.')
        {
            return path.length() > (iterIndex + 1);
        }
    }
    
    return false;
}

template <int32_t _Length>
int32_t Path::GetRandomFileName(const std::span<char8_t, _Length>& destStr)
{
    return GetRandomFileName(&destStr[0], _Length);
}

template <int32_t _Length>
int32_t Path::GetTempPath(const std::span<char8_t, _Length>& destStr)
{
    return GetTempPath(&destStr[0], _Length);
}

constexpr bool Path::IsDirectorySeparator(char8_t ch) noexcept
{
    return ch == AltDirectorySeparatorChar || ch == DirectorySeparatorChar;
}

constexpr bool Path::IsValidDriveChar(char8_t ch) noexcept
{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

}

#if TGON_PLATFORM_WINDOWS
#include "Windows/WindowsPath.inl"
#elif TGON_PLATFORM_MACOS
#include "Posix/PosixPath.inl"
#endif
