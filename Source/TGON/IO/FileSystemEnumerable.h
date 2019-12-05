/**
 * @file    FileSystemEnumerable.h
 * @author  ggomdyu
 * @since   09/28/2019
 */

#pragma once

namespace tgon
{

enum class SearchOption
{
    TopDirectoryOnly,
    AllDirectories,
};

class FileSystemEnumerable
{
/**@section Constructor */
public:
    FileSystemEnumerable() = delete;
    
/**@section Method */
public:
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
};

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateDirectories(const char* path, const _HandlerType& handler)
{
    EnumerateDirectories(path, "*", handler);
}

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateDirectories(const char* path, const char* searchPattern, const _HandlerType& handler)
{
    EnumerateDirectories(path, searchPattern, SearchOption::TopDirectoryOnly, handler);
}

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateFiles(const char* path, const _HandlerType& handler)
{
    EnumerateFiles(path, "*", handler);
}

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateFiles(const char* path, const char* searchPattern, const _HandlerType& handler)
{
    EnumerateFiles(path, searchPattern, SearchOption::TopDirectoryOnly, handler);
}

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateFileSystemEntries(const char* path, const _HandlerType& handler)
{
    EnumerateFileSystemEntries(path, "*", handler);
}

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateFileSystemEntries(const char* path, const char* searchPattern, const _HandlerType& handler)
{
    EnumerateFileSystemEntries(path, searchPattern, SearchOption::TopDirectoryOnly, handler);
}

} /* namespace tgon */

#if TGON_PLATFORM_WINDOWS
#include "Windows/WindowsFileSystemEnumerable.inl"
#elif TGON_PLATFORM_MACOS
#include "Unix/UnixFileSystemEnumerable.inl"
#endif
