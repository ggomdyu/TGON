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

class Directory
{
/**@section Constructor */
public:
    Directory() = delete;
    
/**@section Method */
public:
    static DirectoryInfo CreateDirectory(const std::string_view& path);
    static bool Delete(const std::string_view& path, bool recursive = false);
//    static IEnumerable<string> EnumerateDirectories(const std::string_view& path);
//    static IEnumerable<string> EnumerateDirectories(const std::string_view& path, const std::string_view& searchPattern);
//    static IEnumerable<string> EnumerateDirectories(const std::string_view& path, const std::string_view& searchPattern, SearchOption searchOption);
//    static IEnumerable<string> EnumerateDirectories(const std::string_view& path, const std::string_view& searchPattern, EnumerationOptions enumerationOptions);
//    static IEnumerable<string> EnumerateFiles(const std::string_view& path);
//    static IEnumerable<string> EnumerateFiles(const std::string_view& path, const std::string_view& searchPattern);
//    static IEnumerable<string> EnumerateFiles(const std::string_view& path, const std::string_view& searchPattern, SearchOption searchOption);
//    static IEnumerable<string> EnumerateFiles(const std::string_view& path, const std::string_view& searchPattern, EnumerationOptions enumerationOptions);
//    static IEnumerable<string> EnumerateFileSystemEntries(const std::string_view& path);
//    static IEnumerable<string> EnumerateFileSystemEntries(const std::string_view& path, const std::string_view& searchPattern);
//    static IEnumerable<string> EnumerateFileSystemEntries(const std::string_view& path, const std::string_view& searchPattern, SearchOption searchOption);
//    static IEnumerable<string> EnumerateFileSystemEntries(const std::string_view& path, const std::string_view& searchPattern, EnumerationOptions enumerationOptions);
    static bool Exists(const std::string_view& path);
//    static DateTime GetCreationTime(const std::string_view& path);
//    static DateTime GetCreationTimeUtc(const std::string_view& path);
    static std::string GetCurrentDirectory();
    static int32_t GetCurrentDirectory(char* destStr, int32_t destStrBufferLen);
    template <int32_t Length>
    static int32_t GetCurrentDirectory(const gsl::span<char, Length>& destStr);
    static std::vector<std::string> GetDirectories(const std::string_view& path);
//    static string[] GetDirectories(const std::string_view& path, const std::string_view& searchPattern);
//    static string[] GetDirectories(const std::string_view& path, const std::string_view& searchPattern, SearchOption searchOption);
//    static string[] GetDirectories(const std::string_view& path, const std::string_view& searchPattern, EnumerationOptions enumerationOptions);
//    static string GetDirectoryRoot(const std::string_view& path);
    static std::vector<std::string>  GetFiles(const std::string_view& path);
//    static string[] GetFiles(const std::string_view& path, const std::string_view& searchPattern);
//    static string[] GetFiles(const std::string_view& path, const std::string_view& searchPattern, SearchOption searchOption);
//    static string[] GetFiles(const std::string_view& path, const std::string_view& searchPattern, EnumerationOptions enumerationOptions);
//    static string[] GetFileSystemEntries(const std::string_view& path);
//    static string[] GetFileSystemEntries(const std::string_view& path, const std::string_view& searchPattern);
//    static string[] GetFileSystemEntries(const std::string_view& path, const std::string_view& searchPattern, SearchOption searchOption);
//    static string[] GetFileSystemEntries(const std::string_view& path, const std::string_view& searchPattern, EnumerationOptions enumerationOptions);
//    static DateTime GetLastAccessTime(const std::string_view& path);
//    static DateTime GetLastAccessTimeUtc(const std::string_view& path);
//    static DateTime GetLastWriteTime(const std::string_view& path);
//    static DateTime GetLastWriteTimeUtc(const std::string_view& path);
    static std::vector<std::string> GetLogicalDrives();
    static DirectoryInfo GetParent(const std::string_view& path);
    static bool Move(const std::string_view& srcPath, const std::string_view& destPath);
//    static void SetCreationTime(const std::string_view& path, DateTime creationTime);
//    static void SetCreationTimeUtc(const std::string_view& path, DateTime creationTimeUtc);
//    static void SetCurrentDirectory(const std::string_view& path);
//    static void SetLastAccessTime(const std::string_view& path, DateTime lastAccessTime);
//    static void SetLastAccessTimeUtc(const std::string_view& path, DateTime lastAccessTimeUtc);
//    static void SetLastWriteTime(const std::string_view& path, DateTime lastWriteTime);
//    static void SetLastWriteTimeUtc(const std::string_view& path, DateTime lastWriteTimeUtc);
};

template <int32_t Length>
inline int32_t Directory::GetCurrentDirectory(const gsl::span<char, Length>& destStr)
{
    return GetCurrentDirectory(destStr.data(), Length);
}

} /* namespace tgon */
