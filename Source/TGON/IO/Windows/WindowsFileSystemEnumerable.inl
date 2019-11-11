/**
 * @file    WindowsFileSystemEnumerable.inl
 * @author  ggomdyu
 * @since   11/09/2019
 */

#pragma once
#include <deque>
#include <array>

#include "Core/TypeTraits.h"
#include "Platform/Windows/Windows.h"

#include "../Path.h"
#include "../FileSystemEnumerable.h"

namespace tgon
{

thread_local extern std::array<wchar_t, 16383> g_tempUtf16Buffer;

namespace detail
{

template <typename _HandlerType>
inline void InternalEnumerateAllDirectories(const char* path, const char* searchPattern, uint8_t filterType, const _HandlerType& handler)
{
    std::string_view searchPatternStr = searchPattern;

    std::array<char, 8192> tempPathStr;
    int32_t combinedPathLen = Path::Combine(path, searchPattern, &tempPathStr[0], static_cast<int32_t>(tempPathStr.size()));
    std::deque<std::string> directories(1, std::string(tempPathStr.data(), combinedPathLen));

    do
    {
        const std::string& currPath = directories.front();
        
        int32_t utf16PathBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(currPath.data()), static_cast<int32_t>(currPath.length()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size()));
        if (utf16PathBytes == -1)
        {
            continue;
        }

        WIN32_FIND_DATAW findData;
        HANDLE handle = FindFirstFileW(reinterpret_cast<const wchar_t*>(&g_tempUtf16Buffer[0]), &findData);
        if (handle != INVALID_HANDLE_VALUE)
        {
            std::array<char, MAX_PATH> utf8FileName;

            do
            {
                if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    // Ignore the . and ..
                    if (findData.cFileName[0] == L'.' && (findData.cFileName[1] == L'\0' || (findData.cFileName[1] == L'.' && findData.cFileName[2] == L'\0')))
                    {
                        continue;
                    }

                    int32_t utf8FileNameBytes = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(findData.cFileName), static_cast<int32_t>(wcslen(findData.cFileName) * 2), reinterpret_cast<std::byte*>(&utf8FileName[0]), static_cast<int32_t>(utf8FileName.size()));
                    if (utf8FileNameBytes == -1)
                    {
                        continue;
                    }

                    std::string nextSearchDirectoryPath = Path::Combine(currPath.substr(0, currPath.size() - searchPatternStr.size()), {&utf8FileName[0], static_cast<size_t>(utf8FileNameBytes)});
                    nextSearchDirectoryPath += Path::DirectorySeparatorChar;
                    nextSearchDirectoryPath += searchPatternStr;

                    directories.push_back(std::move(nextSearchDirectoryPath));
                }

                if (findData.dwFileAttributes & filterType)
                {
                    int32_t utf8FileNameBytes = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(findData.cFileName), static_cast<int32_t>(wcslen(findData.cFileName) * 2), reinterpret_cast<std::byte*>(&utf8FileName[0]), static_cast<int32_t>(utf8FileName.size()));
                    if (utf8FileNameBytes == -1)
                    {
                        continue;
                    }

                    int32_t newPathLen = Path::Combine(currPath.substr(0, currPath.size() - searchPatternStr.size()), {&utf8FileName[0], static_cast<size_t>(utf8FileNameBytes)}, &tempPathStr[0], static_cast<int32_t>(tempPathStr.size()));
                    if constexpr (std::is_same_v<typename FunctionTraits<_HandlerType>::ReturnType, bool>)
                    {
                        if (handler({&tempPathStr[0], static_cast<size_t>(newPathLen)}) == false)
                        {
                            break;
                        }
                    }
                    else
                    {
                        handler({&tempPathStr[0], static_cast<size_t>(newPathLen)});
                    }
                }
            } while (FindNextFileW(handle, &findData) == TRUE);

            FindClose(handle);
        }

        directories.pop_front();
    }
    while (directories.empty() == false);
}

template <typename _HandlerType>
void InternalEnumerateTopDirectoryOnly(const char* path, const char* searchPattern, DWORD filterType, const _HandlerType& handler)
{
    std::string_view pathStr = path;

    std::array<char, 8192> tempPathStr;
    int32_t combinedPathLen = Path::Combine(pathStr, searchPattern, &tempPathStr[0], static_cast<int32_t>(tempPathStr.size()));
    int32_t utf16PathBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(tempPathStr.data()), static_cast<int32_t>(combinedPathLen), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size()));
    if (utf16PathBytes == -1)
    {
        return;
    }

    WIN32_FIND_DATAW findData;
    HANDLE handle = FindFirstFileW(reinterpret_cast<const wchar_t*>(&g_tempUtf16Buffer[0]), &findData);
    if (handle != INVALID_HANDLE_VALUE)
    {
        std::array<char, MAX_PATH> utf8FileName;

        do
        {
            if (findData.dwFileAttributes & filterType)
            {
                // Ignore the . and ..
                if (findData.cFileName[0] == L'.' && (findData.cFileName[1] == L'\0' || (findData.cFileName[1] == L'.' && findData.cFileName[2] == L'\0')))
                {
                    continue;
                }

                int32_t utf8FileNameBytes = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(findData.cFileName), static_cast<int32_t>(wcslen(findData.cFileName) * 2), reinterpret_cast<std::byte*>(&utf8FileName[0]), static_cast<int32_t>(utf8FileName.size()));
                if (utf8FileNameBytes == -1)
                {
                    continue;
                }

                int32_t newPathLen = Path::Combine(pathStr, {&utf8FileName[0], static_cast<size_t>(utf8FileNameBytes)}, &tempPathStr[0], static_cast<int32_t>(tempPathStr.size()));
                if constexpr (std::is_same_v<typename FunctionTraits<_HandlerType>::ReturnType, bool>)
                {
                    if (handler({&tempPathStr[0], static_cast<size_t>(newPathLen)}) == false)
                    {
                        break;
                    }
                }
                else
                {
                    handler({&tempPathStr[0], static_cast<size_t>(newPathLen)});
                }
            }
        } while (FindNextFileW(handle, &findData) == TRUE);

        FindClose(handle);
    }
}

} /* namespace detail */

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateDirectories(const char* path, const char* searchPattern, SearchOption searchOption, const _HandlerType& handler)
{
    if (searchOption == SearchOption::AllDirectories)
    {
        detail::InternalEnumerateAllDirectories(path, searchPattern, FILE_ATTRIBUTE_DIRECTORY, handler);
    }
    else
    {
        detail::InternalEnumerateTopDirectoryOnly(path, searchPattern, FILE_ATTRIBUTE_DIRECTORY, handler);
    }
}

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateFiles(const char* path, const char* searchPattern, SearchOption searchOption, const _HandlerType& handler)
{
    if (searchOption == SearchOption::AllDirectories)
    {
        detail::InternalEnumerateAllDirectories(path, searchPattern, FILE_ATTRIBUTE_ARCHIVE, handler);
    }
    else
    {
        detail::InternalEnumerateTopDirectoryOnly(path, searchPattern, FILE_ATTRIBUTE_ARCHIVE, handler);
    }
}

template <typename _HandlerType>
inline void FileSystemEnumerable::EnumerateFileSystemEntries(const char* path, const char* searchPattern, SearchOption searchOption, const _HandlerType& handler)
{
    if (searchOption == SearchOption::AllDirectories)
    {
        detail::InternalEnumerateAllDirectories(path, searchPattern, FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_ARCHIVE, handler);
    }
    else
    {
        detail::InternalEnumerateTopDirectoryOnly(path, searchPattern, FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_ARCHIVE, handler);
    }
}

} /* namespace tgon */
