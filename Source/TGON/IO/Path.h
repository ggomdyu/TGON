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
    static std::optional<std::string> Combine(const std::string_view& path1, const std::string_view& path2);
    static int32_t Combine(const std::string_view& path1, const std::string_view& path2, char* destStr, int32_t destStrBufferLen);
    template <int32_t Length>
    static int32_t Combine(const std::string_view& path1, const std::string_view& path2, const gsl::span<char, Length>& destStr);
    static bool IsPathRooted(const std::string_view& path);
    static std::string_view GetExtension(const std::string_view& path);
    static std::string_view GetFileName(const std::string_view& path);
    static std::string_view GetFileNameWithoutExtension(const std::string_view& path);
    static std::optional<std::string> GetDirectoryName(const std::string_view& path);
    static int32_t GetDirectoryName(const std::string_view& path, char* destStr, int32_t destStrBufferLen);
    template <int32_t Length>
    static int32_t GetDirectoryName(const std::string_view& path, const gsl::span<char, Length>& destStr);
    static bool HasExtension(const std::string_view& path);
    static std::optional<std::string> ChangeExtension(const std::string_view& path, const std::string_view& extension);
    static int32_t ChangeExtension(const std::string_view& path, const std::string_view& extension, char* destStr);
    static std::optional<std::string> GetFullPath(const std::string_view& path);
    static int32_t GetFullPath(const std::string_view& path, char* destStr, int32_t destStrBufferLen);
    template <int32_t Length>
    static int32_t GetFullPath(const std::string_view& path, const gsl::span<char, Length>& destStr);
//    static std::string GetFullPath(const std::string_view& path, const std::string_view& basePath);
//    static std::string GetPathRoot(const std::string_view& path);
//    static std::string GetRandomFileName();
    static std::optional<std::string> GetTempPath();
    static int32_t GetTempPath(char* destStr, int32_t destStrBufferLen);
    template <int32_t Length>
    static int32_t GetTempPath(const gsl::span<char, Length>& destStr);
    static gsl::span<const char> GetInvalidFileNameChars() noexcept;
    static gsl::span<const char> GetInvalidPathChars() noexcept;

private:
    static bool IsValidDriveChar(char ch) noexcept;
    static bool IsDirectorySeparator(char ch) noexcept;

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
    return Combine( path1, path2, &destStr[0], destStr.Length());
}

template <int32_t Length>
inline int32_t Path::GetDirectoryName(const std::string_view& path, const gsl::span<char, Length>& destStr)
{
    return GetDirectoryName(path, &destStr[0], destStr.Length());
}

template <int32_t Length>
inline int32_t Path::GetFullPath(const std::string_view& path, const gsl::span<char, Length>& destStr)
{
    return GetFullPath(path, &destStr[0], destStr.Length());
}

template <int32_t Length>
inline int32_t Path::GetTempPath(const gsl::span<char, Length>& destStr)
{
    return GetTempPath(&destStr[0], destStr.Length());
}

} /* namespace tgon */
