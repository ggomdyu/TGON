#pragma once

#include <unistd.h>
#include <dirent.h>
#include <fnmatch.h>
#include <deque>
#include <array>

#include "Core/TypeTraits.h"

#include "../Path.h"
#include "../FileSystemEnumerable.h"

namespace tg
{
namespace detail
{

template <typename _HandlerType>
inline void InternalEnumerateAllDirectories(const char8_t* path, const char8_t* searchPattern, uint8_t filterType, const _HandlerType& handler)
{
    std::deque<std::u8string> directories(1, std::u8string(path));
    std::array<char8_t, 8192> newPath;
    
    do
    {
        const std::u8string& currPath = directories.front();
        
        DIR* dir = opendir(reinterpret_cast<const char*>(currPath.data()));
        if (dir != nullptr)
        {
            struct dirent* ent;
            while ((ent = readdir(dir)) != nullptr)
            {   
                if (ent->d_type & DT_DIR)
                {
                    // Ignore the . and ..
                    if ((ent->d_namlen == 1 && ent->d_name[0] == '.') || (ent->d_namlen == 2 && !strcmp(ent->d_name, "..")))
                    {
                        continue;
                    }
                    
                    directories.push_back(Path::Combine(currPath, {reinterpret_cast<const char8_t*>(ent->d_name), ent->d_namlen}));
                }
                
                if (ent->d_type & filterType)
                {
                    // Check the file name matched with wildcards
                    if (fnmatch(reinterpret_cast<const char*>(searchPattern), ent->d_name, FNM_PATHNAME) != 0)
                    {
                        continue;
                    }
                    
                    int32_t newPathLen = Path::Combine(currPath, {reinterpret_cast<const char8_t*>(ent->d_name), ent->d_namlen}, newPath.data(), static_cast<int32_t>(newPath.size()));
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
inline void InternalEnumerateTopDirectoryOnly(const char8_t* path, const char8_t* searchPattern, uint8_t filterType, const _HandlerType& handler)
{
    DIR* dir = opendir(reinterpret_cast<const char*>(path));
    if (dir != nullptr)
    {
        std::array<char8_t, 8192> newPath;
        
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
                if (fnmatch(reinterpret_cast<const char*>(searchPattern), reinterpret_cast<const char*>(ent->d_name), FNM_PATHNAME) != 0)
                {
                    continue;
                }
                
                int32_t newPathLen = Path::Combine(path, {reinterpret_cast<const char8_t*>(ent->d_name), ent->d_namlen}, newPath.data(), static_cast<int32_t>(newPath.size()));
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

}

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateDirectories(const char8_t* path, const char8_t* searchPattern, SearchOption searchOption, const _HandlerType& handler)
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
inline void FileSystemEnumerable::EnumerateFiles(const char8_t* path, const char8_t* searchPattern, SearchOption searchOption, const _HandlerType& handler)
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
inline void FileSystemEnumerable::EnumerateFileSystemEntries(const char8_t* path, const char8_t* searchPattern, SearchOption searchOption, const _HandlerType& handler)
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

}
