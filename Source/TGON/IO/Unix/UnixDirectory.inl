/**
 * @file    UnixDirectory.inl
 * @author  ggomdyu
 * @since   10/30/2019
 */

#pragma once
#include <unistd.h>
#include <dirent.h>
#include <fnmatch.h>
#include <deque>

#include "Core/TypeTraits.h"
#include "IO/Path.h"

namespace tgon
{
namespace detail
{

template <typename _HandlerType>
inline void InternalEnumerateAllDirectories(const char* path, const char* searchPattern, uint8_t filterType, const _HandlerType& handler)
{
    std::deque<std::string> directories(1, std::string(path));
    
    do
    {
        std::string currPath = std::move(directories.front());
        directories.pop_front();

        DIR* dir;
        if ((dir = opendir(currPath.data())) != nullptr)
        {
            struct dirent* ent;
            while ((ent = readdir(dir)) != nullptr)
            {
                // Ignore the . and ..
                if ((ent->d_namlen == 1 && ent->d_name[0] == '.') || (ent->d_namlen == 2 && !strcmp(ent->d_name, "..")))
                {
                    continue;
                }
                
                if (ent->d_type == DT_DIR)
                {
                    directories.push_back(Path::Combine(currPath, {ent->d_name, ent->d_namlen}));
                }
                
                if (ent->d_type == filterType)
                {
                    // Check the file name matched with wildcards
                    if (fnmatch(searchPattern, ent->d_name, FNM_PATHNAME) != 0)
                    {
                        continue;
                    }
                    
                    std::string newPath = Path::Combine(currPath, {ent->d_name, ent->d_namlen});
                    if constexpr (std::is_same_v<typename FunctionTraits<_HandlerType>::ReturnType, bool>)
                    {
                        if (handler(std::move(newPath)) == false)
                        {
                            return;
                        }
                    }
                    else
                    {
                        handler(std::move(newPath));
                    }
                }
            }
            closedir(dir);
        }
    }
    while (directories.empty() == false);
}

template <typename _HandlerType>
inline void InternalEnumerateTopDirectoryOnly(const char* path, const char* searchPattern, uint8_t filterType, const _HandlerType& handler)
{
    DIR* dir;
    if ((dir = opendir(path)) != nullptr)
    {
        struct dirent* ent;
        while ((ent = readdir(dir)) != nullptr)
        {
            if (ent->d_type == filterType)
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
                
                std::string newPath = Path::Combine(path, {ent->d_name, ent->d_namlen});
                if constexpr (std::is_same_v<typename FunctionTraits<_HandlerType>::ReturnType, bool>)
                {
                    if (handler({ent->d_name, ent->d_namlen}) == false)
                    {
                        break;
                    }
                }
                else
                {
                    handler({ent->d_name, ent->d_namlen});
                }
            }
        }
        closedir(dir);
    }
}

} /* namespace detail */

template <typename _HandlerType>
inline void Directory::EnumerateDirectories(const char* path, const char* searchPattern, SearchOption searchOption, const _HandlerType& handler)
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
inline void Directory::EnumerateFiles(const char* path, const char* searchPattern, SearchOption searchOption, const _HandlerType& handler)
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

} /* namespace tgon */
