#pragma once

namespace tg
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
    FileSystemEnumerable::EnumerateDirectories(path, "*", handler);
}

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateDirectories(const char* path, const char* searchPattern, const _HandlerType& handler)
{
    FileSystemEnumerable::EnumerateDirectories(path, searchPattern, SearchOption::TopDirectoryOnly, handler);
}

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateFiles(const char* path, const _HandlerType& handler)
{
    FileSystemEnumerable::EnumerateFiles(path, "*", handler);
}

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateFiles(const char* path, const char* searchPattern, const _HandlerType& handler)
{
    FileSystemEnumerable::EnumerateFiles(path, searchPattern, SearchOption::TopDirectoryOnly, handler);
}

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateFileSystemEntries(const char* path, const _HandlerType& handler)
{
    FileSystemEnumerable::EnumerateFileSystemEntries(path, "*", handler);
}

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateFileSystemEntries(const char* path, const char* searchPattern, const _HandlerType& handler)
{
    FileSystemEnumerable::EnumerateFileSystemEntries(path, searchPattern, SearchOption::TopDirectoryOnly, handler);
}

}

#if TGON_PLATFORM_WINDOWS
#include "Windows/WindowsFileSystemEnumerable.inl"
#elif TGON_PLATFORM_MACOS
#include "Unix/UnixFileSystemEnumerable.inl"
#endif
