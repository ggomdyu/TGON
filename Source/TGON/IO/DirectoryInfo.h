/**
 * @file    DirectoryInfo.h
 * @author  ggomdyu
 * @since   09/28/2019
 */

#pragma once
#include <string>
#include <vector>

#include "Platform/Config.h"

#include "FileSystemEnumerable.h"

namespace tgon
{

struct FullPathTag {};

class DirectoryInfo
{
/**@section Constructor */
public:
    explicit DirectoryInfo(const std::string_view& path);
    DirectoryInfo(const std::string_view& path, FullPathTag);
    
public:
    void Create() const;
    DirectoryInfo CreateSubdirectory(const std::string_view& path) const;
    bool Delete(bool recursive = false) const;
    bool IsExists() const;
    bool MoveTo(const char* destDirName) const;
    std::string_view GetName() const noexcept;
    DirectoryInfo GetRoot() const;
    DirectoryInfo GetParent() const;
    std::vector<std::string> GetDirectories(const char* searchPattern = "*", SearchOption searchOption = SearchOption::TopDirectoryOnly);
    std::vector<std::string> GetFiles(const char* searchPattern = "*", SearchOption searchOption = SearchOption::TopDirectoryOnly);
    std::vector<std::string> GetFileSystemEntries(const char* searchPattern = "*", SearchOption searchOption = SearchOption::TopDirectoryOnly);
    template <typename _HandlerType>
    void EnumerateDirectories(const _HandlerType& handler) const;
    template <typename _HandlerType>
    void EnumerateDirectories(const char* searchPattern, const _HandlerType& handler) const;
    template <typename _HandlerType>
    void EnumerateDirectories(const char* searchPattern, SearchOption searchOption, const _HandlerType& handler) const;
    template <typename _HandlerType>
    void EnumerateFiles(const _HandlerType& handler) const;
    template <typename _HandlerType>
    void EnumerateFiles(const char* searchPattern, const _HandlerType& handler) const;
    template <typename _HandlerType>
    void EnumerateFiles(const char* searchPattern, SearchOption searchOption, const _HandlerType& handler) const;
    template <typename _HandlerType>
    void EnumerateFileSystemEntries(const _HandlerType& handler);
    template <typename _HandlerType>
    void EnumerateFileSystemEntries(const char* searchPattern, const _HandlerType& handler);
    template <typename _HandlerType>
    void EnumerateFileSystemEntries(const char* searchPattern, SearchOption searchOption, const _HandlerType& handler);
    const std::string& ToString() const noexcept;
    
/**@section Variable */
private:
    std::string m_fullPath;
};

template <typename _HandlerType>
inline void DirectoryInfo::EnumerateDirectories(const _HandlerType& handler) const
{
    FileSystemEnumerable::EnumerateDirectories(m_fullPath.c_str(), handler);
}

template <typename _HandlerType>
inline void DirectoryInfo::EnumerateDirectories(const char* searchPattern, const _HandlerType& handler) const
{
    FileSystemEnumerable::EnumerateDirectories(m_fullPath.c_str(), searchPattern, handler);
}

template <typename _HandlerType>
inline void DirectoryInfo::EnumerateDirectories(const char* searchPattern, SearchOption searchOption, const _HandlerType& handler) const
{
    FileSystemEnumerable::EnumerateDirectories(m_fullPath.c_str(), searchPattern, searchOption, handler);
}

template <typename _HandlerType>
inline void DirectoryInfo::EnumerateFiles(const _HandlerType& handler) const
{
    FileSystemEnumerable::EnumerateFiles(m_fullPath.c_str(), handler);
}

template <typename _HandlerType>
inline void DirectoryInfo::EnumerateFiles(const char* searchPattern, const _HandlerType& handler) const
{
    FileSystemEnumerable::EnumerateFiles(m_fullPath.c_str(), searchPattern, handler);
}

template <typename _HandlerType>
inline void DirectoryInfo::EnumerateFiles(const char* searchPattern, SearchOption searchOption, const _HandlerType& handler) const
{
    FileSystemEnumerable::EnumerateFiles(m_fullPath.c_str(), searchPattern, searchOption, handler);
}

template <typename _HandlerType>
inline void DirectoryInfo::EnumerateFileSystemEntries(const _HandlerType& handler)
{
    FileSystemEnumerable::EnumerateFileSystemEntries(m_fullPath.c_str(), handler);
}

template <typename _HandlerType>
inline void DirectoryInfo::EnumerateFileSystemEntries(const char* searchPattern, const _HandlerType& handler)
{
    FileSystemEnumerable::EnumerateFileSystemEntries(m_fullPath.c_str(), searchPattern, handler);
}

template <typename _HandlerType>
inline void DirectoryInfo::EnumerateFileSystemEntries(const char* searchPattern, SearchOption searchOption, const _HandlerType& handler)
{
    FileSystemEnumerable::EnumerateFileSystemEntries(m_fullPath.c_str(), searchPattern, searchOption, handler);
}

} /* namespace tgon */
