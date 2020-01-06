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

#include "DirectoryInfo.h"
#include "File.h"
#include "FileSystemEnumerable.h"

namespace tgon
{

class Directory final
{
/**@section Constructor */
public:
    Directory() = delete;
    
/**@section Method */
public:
    static DirectoryInfo CreateDirectory(const std::string_view& path);
    static bool Delete(const char* path, bool recursive = false);
    static bool Exists(const char* path);
    static bool Move(const char* srcPath, const char* destPath);
    static bool SetCurrentDirectory(const char* path);
    static bool SetCreationTime(const char* path, const DateTime& creationTime);
    static bool SetCreationTimeUtc(const char* path, const DateTime& creationTimeUtc);
    static bool SetLastAccessTime(const char* path, const DateTime& lastAccessTime);
    static bool SetLastAccessTimeUtc(const char* path, const DateTime& lastAccessTimeUtc);
    static bool SetLastWriteTime(const char* path, const DateTime& lastWriteTime);
    static bool SetLastWriteTimeUtc(const char* path, const DateTime& lastWriteTimeUtc);
    static std::optional<DateTime> GetCreationTime(const char* path);
    static std::optional<DateTime> GetCreationTimeUtc(const char* path);
    static std::optional<DateTime> GetLastAccessTime(const char* path);
    static std::optional<DateTime> GetLastAccessTimeUtc(const char* path);
    static std::optional<DateTime> GetLastWriteTime(const char* path);
    static std::optional<DateTime> GetLastWriteTimeUtc(const char* path);
    static std::string GetCurrentDirectory();
    static int32_t GetCurrentDirectory(char* destStr, int32_t destStrBufferLen);
    template <int32_t Length>
    static int32_t GetCurrentDirectory(const gsl::span<char, Length>& destStr);
    static std::string GetDirectoryRoot(const std::string_view& path);
    static std::vector<std::string> GetLogicalDrives();
    static DirectoryInfo GetParent(const std::string_view& path);
    static std::vector<std::string> GetDirectories(const char* path, const char* searchPattern = "*", SearchOption searchOption = SearchOption::TopDirectoryOnly);
    static std::vector<std::string> GetFiles(const char* path, const char* searchPattern = "*", SearchOption searchOption = SearchOption::TopDirectoryOnly);
    static std::vector<std::string> GetFileSystemEntries(const char* path, const char* searchPattern = "*", SearchOption searchOption = SearchOption::TopDirectoryOnly);
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
    template <typename _HandlerType>
    static void EnumerateFileSystemEntries(const char* path, const _HandlerType& handler);
    template <typename _HandlerType>
    static void EnumerateFileSystemEntries(const char* path, const char* searchPattern, const _HandlerType& handler);
    template <typename _HandlerType>
    static void EnumerateFileSystemEntries(const char* path, const char* searchPattern, SearchOption searchOption, const _HandlerType& handler);
    
private:
    static bool InternalCreateDirectory(const char* path);
};

template <int32_t Length>
inline int32_t Directory::GetCurrentDirectory(const gsl::span<char, Length>& destStr)
{
    return GetCurrentDirectory(destStr.data(), Length);
}

template <typename _HandlerType>
inline void Directory::EnumerateDirectories(const char* path, const _HandlerType& handler)
{
    return FileSystemEnumerable::EnumerateDirectories(path, handler);
}

template <typename _HandlerType>
inline void Directory::EnumerateDirectories(const char* path, const char* searchPattern, const _HandlerType& handler)
{
    return FileSystemEnumerable::EnumerateDirectories(path, searchPattern, handler);
}

template <typename _HandlerType>
inline void Directory::EnumerateDirectories(const char* path, const char* searchPattern, SearchOption searchOption, const _HandlerType& handler)
{
    return FileSystemEnumerable::EnumerateDirectories(path, searchPattern, searchOption, handler);
}

template <typename _HandlerType>
inline void Directory::EnumerateFiles(const char* path, const _HandlerType& handler)
{
    return FileSystemEnumerable::EnumerateFiles(path, handler);
}

template <typename _HandlerType>
inline void Directory::EnumerateFiles(const char* path, const char* searchPattern, const _HandlerType& handler)
{
    return FileSystemEnumerable::EnumerateFiles(path, searchPattern, handler);
}

template <typename _HandlerType>
inline void Directory::EnumerateFiles(const char* path, const char* searchPattern, SearchOption searchOption, const _HandlerType& handler)
{
    return FileSystemEnumerable::EnumerateFiles(path, searchPattern, searchOption, handler);
}

template <typename _HandlerType>
inline void Directory::EnumerateFileSystemEntries(const char* path, const _HandlerType& handler)
{
    return FileSystemEnumerable::EnumerateFileSystemEntries(path, handler);
}

template <typename _HandlerType>
inline void Directory::EnumerateFileSystemEntries(const char* path, const char* searchPattern, const _HandlerType& handler)
{
    return FileSystemEnumerable::EnumerateFileSystemEntries(path, searchPattern, handler);
}

template <typename _HandlerType>
inline void Directory::EnumerateFileSystemEntries(const char* path, const char* searchPattern, SearchOption searchOption, const _HandlerType& handler)
{
    return FileSystemEnumerable::EnumerateFileSystemEntries(path, searchPattern, searchOption, handler);
}

} /* namespace tgon */
