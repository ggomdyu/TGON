#pragma once

#include <array>
#include <deque>

#include "Core/TypeTraits.h"
#include "Platform/Windows/Windows.h"
#include "Text/Encoding.h"

#include "../Path.h"

namespace tg
{
namespace detail
{

template <typename _Callback>
void InternalEnumerateAllDirectories(const char8_t* path, const char8_t* searchPattern, DWORD filterType, const _Callback& callback)
{
    const std::u8string_view searchPatternStr = searchPattern;
    std::deque<std::u8string> directories(1, Path::Combine(path, searchPattern));

    do
    {
        const auto& currentPath = directories.front();
        auto utf16Path = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(currentPath.data()), static_cast<int32_t>(currentPath.length() + 1));

        WIN32_FIND_DATAW findData;
        auto* handle = FindFirstFileW(reinterpret_cast<const wchar_t*>(&utf16Path[0]), &findData);
        if (handle != INVALID_HANDLE_VALUE)
        {
            std::array<char8_t, MAX_PATH> utf8FileName{};

            do
            {
                if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    // Ignore the . and ..
                    if (findData.cFileName[0] == L'.' && (findData.cFileName[1] == L'\0' || (findData.cFileName[1] == L'.' && findData.cFileName[2] == L'\0')))
                    {
                        continue;
                    }

                    const auto utf8FileNameByteCount = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(findData.cFileName), static_cast<int32_t>(wcslen(findData.cFileName) * 2) + 2, reinterpret_cast<std::byte*>(&utf8FileName[0]), static_cast<int32_t>(utf8FileName.size()));
                    if (utf8FileNameByteCount == -1)
                    {
                        continue;
                    }

                    auto nextSearchDirectoryPath = Path::Combine(currentPath.substr(0, currentPath.size() - searchPatternStr.size()), {&utf8FileName[0], static_cast<size_t>(utf8FileNameByteCount - 1)});
                    nextSearchDirectoryPath += Path::DirectorySeparatorChar;
                    nextSearchDirectoryPath += searchPatternStr;

                    directories.push_back(std::move(nextSearchDirectoryPath));
                }

                if (findData.dwFileAttributes & filterType)
                {
                    const auto utf8FileNameByteCount = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(findData.cFileName), static_cast<int32_t>(wcslen(findData.cFileName) * 2) + 2, reinterpret_cast<std::byte*>(&utf8FileName[0]), static_cast<int32_t>(utf8FileName.size()));
                    if (utf8FileNameByteCount == -1)
                    {
                        continue;
                    }

                    auto newPath = Path::Combine(currentPath.substr(0, currentPath.size() - searchPatternStr.size()), {&utf8FileName[0], static_cast<size_t>(utf8FileNameByteCount - 1)});
                    if constexpr (std::is_same_v<typename FunctionTraits<_Callback>::ReturnType, bool>)
                    {
                        if (callback(std::move(newPath)) == false)
                        {
                            return;
                        }
                    }
                    else
                    {
                        callback(std::move(newPath));
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
    const std::u8string_view pathStr = path;

    const auto combinedPath = Path::Combine(pathStr, searchPattern);
    const auto utf16Path = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(combinedPath.data()), static_cast<int32_t>(combinedPath.length() + 1));

    WIN32_FIND_DATAW findData;
    auto* handle = FindFirstFileW(reinterpret_cast<const wchar_t*>(&utf16Path[0]), &findData);
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

                const auto utf8FileNameByteCount = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(findData.cFileName), static_cast<int32_t>(wcslen(findData.cFileName) * 2) + 2, reinterpret_cast<std::byte*>(&utf8FileName[0]), static_cast<int32_t>(utf8FileName.size()));
                if (utf8FileNameByteCount == -1)
                {
                    continue;
                }

                auto newPath = Path::Combine(pathStr, {&utf8FileName[0], static_cast<size_t>(utf8FileNameByteCount - 1)});
                if constexpr (std::is_same_v<typename FunctionTraits<_Callback>::ReturnType, bool>)
                {
                    if (callback(std::move(newPath)) == false)
                    {
                        return;
                    }
                }
                else
                {
                    callback(std::move(newPath));
                }
            }
        } while (FindNextFileW(handle, &findData) == TRUE);

        FindClose(handle);
    }
}

}

template <typename _Callback>
void FileSystemEnumerable::EnumerateDirectories(const char8_t* path, const char8_t* searchPattern, SearchOption searchOption, const _Callback& callback)
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
void FileSystemEnumerable::EnumerateFiles(const char8_t* path, const char8_t* searchPattern, SearchOption searchOption, const _Callback& callback)
{
    if (searchOption == SearchOption::AllDirectories)
    {
        constexpr size_t p = ~FILE_ATTRIBUTE_DIRECTORY;
        detail::InternalEnumerateAllDirectories(path, searchPattern, FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_NORMAL, callback);
    }
    else
    {
        detail::InternalEnumerateTopDirectoryOnly(path, searchPattern, FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_NORMAL, callback);
    }
}

template <typename _Callback>
void FileSystemEnumerable::EnumerateFileSystemEntries(const char8_t* path, const char8_t* searchPattern, SearchOption searchOption, const _Callback& callback)
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