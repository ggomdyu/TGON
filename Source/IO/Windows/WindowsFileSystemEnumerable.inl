#pragma once

#include <deque>
#include <array>

#include "Core/TypeTraits.h"
#include "Text/Encoding.h"
#include "Platform/Windows/Windows.h"

#include "../Path.h"
#include "../FileSystemEnumerable.h"

namespace tg
{

thread_local extern std::array<wchar_t, 16383> g_tempUtf16Buffer;

namespace detail
{

template <typename _Callback>
inline void InternalEnumerateAllDirectories(const char8_t* path, const char8_t* searchPattern, DWORD filterType, const _Callback& callback)
{
    std::u8string_view searchPatternStr = searchPattern;

    std::array<char8_t, 4096> tempPathStr;
    int32_t combinedPathLen = Path::Combine(path, searchPattern, &tempPathStr[0], static_cast<int32_t>(tempPathStr.size()));
    std::deque<std::u8string> directories(1, std::u8string(tempPathStr.data(), static_cast<size_t>(combinedPathLen)));

    do
    {
        const std::u8string& currPath = directories.front();
        if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(currPath.data()), static_cast<int32_t>(currPath.length()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
        {
            continue;
        }

        WIN32_FIND_DATAW findData;
        HANDLE handle = FindFirstFileW(reinterpret_cast<const wchar_t*>(&g_tempUtf16Buffer[0]), &findData);
        if (handle != INVALID_HANDLE_VALUE)
        {
            std::array<char8_t, MAX_PATH> utf8FileName;

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

                    std::u8string nextSearchDirectoryPath = Path::Combine(currPath.substr(0, currPath.size() - searchPatternStr.size()), {&utf8FileName[0], static_cast<size_t>(utf8FileNameBytes)});
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
                    if constexpr (std::is_same_v<typename FunctionTraits<_Callback>::ReturnType, bool>)
                    {
                        if (callback({&tempPathStr[0], static_cast<size_t>(newPathLen)}) == false)
                        {
                            break;
                        }
                    }
                    else
                    {
                        callback({&tempPathStr[0], static_cast<size_t>(newPathLen)});
                    }
                }
            } while (FindNextFileW(handle, &findData) == TRUE);

            FindClose(handle);
        }

        directories.pop_front();
    } while (directories.empty() == false);
}

template <typename _Callback>
void InternalEnumerateTopDirectoryOnly(const char8_t* path, const char8_t* searchPattern, DWORD filterType, const _Callback& callback)
{
    std::u8string_view pathStr = path;

    std::array<char8_t, 4096> tempPathStr;
    int32_t combinedPathLen = Path::Combine(pathStr, searchPattern, &tempPathStr[0], static_cast<int32_t>(tempPathStr.size()));
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(tempPathStr.data()), static_cast<int32_t>(combinedPathLen), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return;
    }

    WIN32_FIND_DATAW findData;
    HANDLE handle = FindFirstFileW(reinterpret_cast<const wchar_t*>(&g_tempUtf16Buffer[0]), &findData);
    if (handle != INVALID_HANDLE_VALUE)
    {
        std::array<char8_t, MAX_PATH> utf8FileName;

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
                if constexpr (std::is_same_v<typename FunctionTraits<_Callback>::ReturnType, bool>)
                {
                    if (callback({&tempPathStr[0], static_cast<size_t>(newPathLen)}) == false)
                    {
                        break;
                    }
                }
                else
                {
                    callback({&tempPathStr[0], static_cast<size_t>(newPathLen)});
                }
            }
        } while (FindNextFileW(handle, &findData) == TRUE);

        FindClose(handle);
    }
}

}

template <typename _Callback>
inline void FileSystemEnumerable::EnumerateDirectories(const char8_t* path, const char8_t* searchPattern, SearchOption searchOption, const _Callback& callback)
{
    if (searchOption == SearchOption::AllDirectories)
    {
        detail::InternalEnumerateAllDirectories(path, searchPattern, FILE_ATTRIBUTE_DIRECTORY, callback);
    }
    else
    {
        detail::InternalEnumerateTopDirectoryOnly(path, searchPattern, FILE_ATTRIBUTE_DIRECTORY, callback);
    }
}

template <typename _Callback>
inline void FileSystemEnumerable::EnumerateFiles(const char8_t* path, const char8_t* searchPattern, SearchOption searchOption, const _Callback& callback)
{
    if (searchOption == SearchOption::AllDirectories)
    {
        detail::InternalEnumerateAllDirectories(path, searchPattern, ~FILE_ATTRIBUTE_DIRECTORY, callback);
    }
    else
    {
        detail::InternalEnumerateTopDirectoryOnly(path, searchPattern, ~FILE_ATTRIBUTE_DIRECTORY, callback);
    }
}

template <typename _Callback>
inline void FileSystemEnumerable::EnumerateFileSystemEntries(const char8_t* path, const char8_t* searchPattern, SearchOption searchOption, const _Callback& callback)
{
    if (searchOption == SearchOption::AllDirectories)
    {
        detail::InternalEnumerateAllDirectories(path, searchPattern, UINT8_MAX, callback);
    }
    else
    {
        detail::InternalEnumerateTopDirectoryOnly(path, searchPattern, UINT8_MAX, callback);
    }
}

}
