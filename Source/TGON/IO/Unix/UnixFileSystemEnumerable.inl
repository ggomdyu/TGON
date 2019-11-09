/**
 * @file    UnixFileSystemEnumerable.inl
 * @author  ggomdyu
 * @since   11/06/2019
 */

#pragma once
#include <unistd.h>
#include <dirent.h>
#include <fnmatch.h>
#include <deque>
#include <array>

#include "Core/TypeTraits.h"

#include "../Path.h"
#include "../FileSystemEnumerable.h"

namespace tgon
{
namespace detail
{

template <typename _HandlerType>
inline void InternalEnumerateAllDirectories(const char* path, const char* searchPattern, uint8_t filterType, const _HandlerType& handler)
{
    std::deque<std::string> directories(1, std::string(path));
    std::array<char, 16384> newPath;
    
    do
    {
        const std::string& currPath = directories.front();
        
        DIR* dir = opendir(currPath.data());
        if (dir != nullptr)
        {
            struct dirent* ent;
            while ((ent = readdir(dir)) != nullptr)
            {
                // Ignore the . and ..
                if ((ent->d_namlen == 1 && ent->d_name[0] == '.') || (ent->d_namlen == 2 && !strcmp(ent->d_name, "..")))
                {
                    continue;
                }
                
                if (ent->d_type & DT_DIR)
                {
                    directories.push_back(Path::Combine(currPath, {ent->d_name, ent->d_namlen}));
                }
                
                if (ent->d_type & filterType)
                {
                    // Check the file name matched with wildcards
                    if (fnmatch(searchPattern, ent->d_name, FNM_PATHNAME) != 0)
                    {
                        continue;
                    }
                    
                    int32_t newPathLen = Path::Combine(currPath, {ent->d_name, ent->d_namlen}, newPath.data(), static_cast<int32_t>(newPath.size()));
                    if constexpr (std::is_same_v<typename FunctionTraits<_HandlerType>::ReturnType, bool>)
                    {
                        if (handler({newPath.data(), static_cast<size_t>(newPathLen)}) == false)
                        {
                            return;
                        }
                    }
                    else
                    {
                        handler({newPath.data(), static_cast<size_t>(newPathLen)});
                    }
                }
            }
            closedir(dir);
        }
        
        directories.pop_front();
    }
    while (directories.empty() == false);
}

template <typename _HandlerType>
inline void InternalEnumerateTopDirectoryOnly(const char* path, const char* searchPattern, uint8_t filterType, const _HandlerType& handler)
{
    DIR* dir = opendir(path);
    if (dir != nullptr)
    {
        std::array<char, 16384> newPath;
        
        struct dirent* ent;
        while ((ent = readdir(dir)) != nullptr)
        {
            if (ent->d_type & filterType)
            {
                // Ignore the . and ..
                if ((ent->d_namlen == 1 && ent->d_name[0] == '.') || (ent->d_namlen == 2 && !strcmp(ent->d_name, "..")))
                {
                    continue;
                }
                
                // Check the file name matched with wildcards
                if (fnmatch(searchPattern, ent->d_name, FNM_PATHNAME) != 0)
                {
                    continue;
                }
                
                int32_t newPathLen = Path::Combine(path, {ent->d_name, ent->d_namlen}, newPath.data(), static_cast<int32_t>(newPath.size()));
                if constexpr (std::is_same_v<typename FunctionTraits<_HandlerType>::ReturnType, bool>)
                {
                    if (handler({newPath.data(), static_cast<size_t>(newPathLen)}) == false)
                    {
                        break;
                    }
                }
                else
                {
                    handler({newPath.data(), static_cast<size_t>(newPathLen)});
                }
            }
        }
        closedir(dir);
    }
}

} /* namespace detail */

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateDirectories(const char* path, const char* searchPattern, SearchOption searchOption, const _HandlerType& handler)
{
    if (searchOption == SearchOption::AllDirectories)
    {
        detail::InternalEnumerateAllDirectories(path, searchPattern, DT_DIR, handler);
    }
    else
    {
        detail::InternalEnumerateTopDirectoryOnly(path, searchPattern, DT_DIR, handler);
    }
}

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateFiles(const char* path, const char* searchPattern, SearchOption searchOption, const _HandlerType& handler)
{
    if (searchOption == SearchOption::AllDirectories)
    {
        detail::InternalEnumerateAllDirectories(path, searchPattern, DT_REG, handler);
    }
    else
    {
        detail::InternalEnumerateTopDirectoryOnly(path, searchPattern, DT_REG, handler);
    }
}

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateFileSystemEntries(const char* path, const char* searchPattern, SearchOption searchOption, const _HandlerType& handler)
{
    if (searchOption == SearchOption::AllDirectories)
    {
        detail::InternalEnumerateAllDirectories(path, searchPattern, DT_DIR | DT_REG, handler);
    }
    else
    {
        detail::InternalEnumerateTopDirectoryOnly(path, searchPattern, DT_DIR | DT_REG, handler);
    }
}

} /* namespace tgon */
