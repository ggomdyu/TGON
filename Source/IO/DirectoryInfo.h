#pragma once

#include <string>
#include <vector>

#include "FileSystemEnumerable.h"

namespace tg
{

struct FullPathTag {};

class DirectoryInfo final
{
/**@section Constructor */
public:
    explicit DirectoryInfo(const std::u8string_view& path);
    DirectoryInfo(const std::u8string_view& path, FullPathTag);
    
public:
    void Create() const;
    [[nodiscard]] DirectoryInfo CreateSubdirectory(const std::u8string_view& path) const;
    bool Delete(bool recursive = false) const;
    [[nodiscard]] bool IsExists() const;
    bool MoveTo(const char8_t* destDirName) const;
    [[nodiscard]] std::u8string_view GetName() const noexcept;
    [[nodiscard]] DirectoryInfo GetRoot() const;
    [[nodiscard]] DirectoryInfo GetParent() const;
    [[nodiscard]] std::vector<std::u8string> GetDirectories(const char8_t* searchPattern = u8"*", SearchOption searchOption = SearchOption::TopDirectoryOnly) const;
    [[nodiscard]] std::vector<std::u8string> GetFiles(const char8_t* searchPattern = u8"*", SearchOption searchOption = SearchOption::TopDirectoryOnly) const;
    [[nodiscard]] std::vector<std::u8string> GetFileSystemEntries(const char8_t* searchPattern = u8"*", SearchOption searchOption = SearchOption::TopDirectoryOnly) const;
    template <typename _Callback>
    void EnumerateDirectories(const _Callback& callback) const;
    template <typename _Callback>
    void EnumerateDirectories(const char8_t* searchPattern, const _Callback& callback) const;
    template <typename _Callback>
    void EnumerateDirectories(const char8_t* searchPattern, SearchOption searchOption, const _Callback& callback) const;
    template <typename _Callback>
    void EnumerateFiles(const _Callback& callback) const;
    template <typename _Callback>
    void EnumerateFiles(const char8_t* searchPattern, const _Callback& callback) const;
    template <typename _Callback>
    void EnumerateFiles(const char8_t* searchPattern, SearchOption searchOption, const _Callback& callback) const;
    template <typename _Callback>
    void EnumerateFileSystemEntries(const _Callback& callback);
    template <typename _Callback>
    void EnumerateFileSystemEntries(const char8_t* searchPattern, const _Callback& callback);
    template <typename _Callback>
    void EnumerateFileSystemEntries(const char8_t* searchPattern, SearchOption searchOption, const _Callback& callback);
    [[nodiscard]] const std::u8string& ToString() const noexcept;
    
/**@section Variable */
private:
    std::u8string m_fullPath;
};

template <typename _Callback>
void DirectoryInfo::EnumerateDirectories(const _Callback& callback) const
{
    FileSystemEnumerable::EnumerateDirectories(m_fullPath.c_str(), callback);
}

template <typename _Callback>
void DirectoryInfo::EnumerateDirectories(const char8_t* searchPattern, const _Callback& callback) const
{
    FileSystemEnumerable::EnumerateDirectories(m_fullPath.c_str(), searchPattern, callback);
}

template <typename _Callback>
void DirectoryInfo::EnumerateDirectories(const char8_t* searchPattern, SearchOption searchOption, const _Callback& callback) const
{
    FileSystemEnumerable::EnumerateDirectories(m_fullPath.c_str(), searchPattern, searchOption, callback);
}

template <typename _Callback>
void DirectoryInfo::EnumerateFiles(const _Callback& callback) const
{
    FileSystemEnumerable::EnumerateFiles(m_fullPath.c_str(), callback);
}

template <typename _Callback>
void DirectoryInfo::EnumerateFiles(const char8_t* searchPattern, const _Callback& callback) const
{
    FileSystemEnumerable::EnumerateFiles(m_fullPath.c_str(), searchPattern, callback);
}

template <typename _Callback>
void DirectoryInfo::EnumerateFiles(const char8_t* searchPattern, SearchOption searchOption, const _Callback& callback) const
{
    FileSystemEnumerable::EnumerateFiles(m_fullPath.c_str(), searchPattern, searchOption, callback);
}

template <typename _Callback>
void DirectoryInfo::EnumerateFileSystemEntries(const _Callback& callback)
{
    FileSystemEnumerable::EnumerateFileSystemEntries(m_fullPath.c_str(), callback);
}

template <typename _Callback>
void DirectoryInfo::EnumerateFileSystemEntries(const char8_t* searchPattern, const _Callback& callback)
{
    FileSystemEnumerable::EnumerateFileSystemEntries(m_fullPath.c_str(), searchPattern, callback);
}

template <typename _Callback>
void DirectoryInfo::EnumerateFileSystemEntries(const char8_t* searchPattern, SearchOption searchOption, const _Callback& callback)
{
    FileSystemEnumerable::EnumerateFileSystemEntries(m_fullPath.c_str(), searchPattern, searchOption, callback);
}

}
