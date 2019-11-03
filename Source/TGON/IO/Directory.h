/**
 * @file    Directory.h
 * @author  ggomdyu
 * @since   09/28/2019
 */

#pragma once
#include <string>
#include <optional>
#include <vector>
#include <gsl/span>

#include "Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsDirectory.h"
#endif

#include "DirectoryInfo.h"

namespace tgon
{

enum class SearchOption
{
    TopDirectoryOnly,
    AllDirectories,
};

class TGON_API Directory
{
/**@section Constructor */
public:
    Directory() = delete;
    
/**@section Method */
public:
    static DirectoryInfo CreateDirectory(const char* path);
    static bool Delete(const char* path, bool recursive = false);
    static bool Exists(const char* path);
    static bool Move(const char* srcPath, const char* destPath);
    static std::string GetCurrentDirectory();
    static int32_t GetCurrentDirectory(char* destStr, int32_t destStrBufferLen);
    template <int32_t Length>
    static int32_t GetCurrentDirectory(const gsl::span<char, Length>& destStr);
    //    static string GetDirectoryRoot(const std::string_view& path);
    static std::vector<std::string> GetLogicalDrives();
    static DirectoryInfo GetParent(const char* path);
    static std::vector<std::string> GetFiles(const char* path, const char* searchPattern = "*", SearchOption searchOption = SearchOption::TopDirectoryOnly);
    static std::vector<std::string> GetDirectories(const char* path, const char* searchPattern = "*", SearchOption searchOption = SearchOption::TopDirectoryOnly);
    template <typename _HandlerType>
    static void EnumerateDirectories(const char* path, const _HandlerType& handler);
    template <typename _HandlerType>
    static void EnumerateDirectories(const char* path, const char* searchPattern, const _HandlerType& handler);
    template <typename _HandlerType>
    static void EnumerateDirectories(const char* path, const char* searchPattern, SearchOption searchOption, const _HandlerType& handler);
    template <typename _HandlerType>
    static void EnumerateFiles(const char* path, const _HandlerType& handler);
    template <typename _HandlerType>
    static void EnumerateFiles(const char* path, const char* searchPattern, const _HandlerType& handler);
    template <typename _HandlerType>
    static void EnumerateFiles(const char* path, const char* searchPattern, SearchOption searchOption, const _HandlerType& handler);
//    static IEnumerable<string> EnumerateFileSystemEntries(const std::string_view& path);
//    static IEnumerable<string> EnumerateFileSystemEntries(const std::string_view& path, const std::string_view& searchPattern);
//    static IEnumerable<string> EnumerateFileSystemEntries(const std::string_view& path, const std::string_view& searchPattern, SearchOption searchOption);
//    static DateTime GetCreationTime(const std::string_view& path);
//    static DateTime GetCreationTimeUtc(const std::string_view& path);
//    static string[] GetFileSystemEntries(const std::string_view& path);
//    static string[] GetFileSystemEntries(const std::string_view& path, const std::string_view& searchPattern);
//    static string[] GetFileSystemEntries(const std::string_view& path, const std::string_view& searchPattern, SearchOption searchOption);
//    static string[] GetFileSystemEntries(const std::string_view& path, const std::string_view& searchPattern, EnumerationOptions enumerationOptions);
//    static DateTime GetLastAccessTime(const std::string_view& path);
//    static DateTime GetLastAccessTimeUtc(const std::string_view& path);
//    static DateTime GetLastWriteTime(const std::string_view& path);
//    static DateTime GetLastWriteTimeUtc(const std::string_view& path);
//    static void SetCreationTime(const std::string_view& path, DateTime creationTime);
//    static void SetCreationTimeUtc(const std::string_view& path, DateTime creationTimeUtc);
//    static void SetCurrentDirectory(const std::string_view& path);
//    static void SetLastAccessTime(const std::string_view& path, DateTime lastAccessTime);
//    static void SetLastAccessTimeUtc(const std::string_view& path, DateTime lastAccessTimeUtc);
//    static void SetLastWriteTime(const std::string_view& path, DateTime lastWriteTime);
//    static void SetLastWriteTimeUtc(const std::string_view& path, DateTime lastWriteTimeUtc);
//    static string[] GetDirectories(const std::string_view& path, const std::string_view& searchPattern, EnumerationOptions enumerationOptions);
//    static IEnumerable<string> EnumerateFiles(const std::string_view& path, const std::string_view& searchPattern, EnumerationOptions enumerationOptions);
//    static string[] GetFiles(const std::string_view& path, const std::string_view& searchPattern, EnumerationOptions enumerationOptions);
//    static IEnumerable<string> EnumerateDirectories(const std::string_view& path, const std::string_view& searchPattern, EnumerationOptions enumerationOptions);
//    static IEnumerable<string> EnumerateFileSystemEntries(const std::string_view& path, const std::string_view& searchPattern, EnumerationOptions enumerationOptions);
};

template <int32_t Length>
inline int32_t Directory::GetCurrentDirectory(const gsl::span<char, Length>& destStr)
{
    return GetCurrentDirectory(destStr.data(), Length);
}

template <typename _HandlerType>
inline void Directory::EnumerateDirectories(const char* path, const _HandlerType& handler)
{
    return EnumerateDirectories(path, "*", handler);
}

template <typename _HandlerType>
inline void Directory::EnumerateDirectories(const char* path, const char* searchPattern, const _HandlerType& handler)
{
    return EnumerateDirectories(path, searchPattern, SearchOption::TopDirectoryOnly, handler);
}

template <typename _HandlerType>
inline void Directory::EnumerateFiles(const char* path, const _HandlerType& handler)
{
    return EnumerateFiles(path, "*", handler);
}

template <typename _HandlerType>
inline void Directory::EnumerateFiles(const char* path, const char* searchPattern, const _HandlerType& handler)
{
    return EnumerateFiles(path, searchPattern, SearchOption::TopDirectoryOnly, handler);
}

} /* namespace tgon */

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsDirectory.inl"
#elif TGON_PLATFORM_MACOS
#   include "Unix/UnixDirectory.inl"
#endif
