#include "PrecompiledHeader.h"

#include <array>
#include <sys/stat.h>

#include "Platform/Windows/Windows.h"

#include "../Directory.h"
#include "../Path.h"

namespace tg
{
namespace
{

#if !defined(S_ISDIR)
constexpr bool S_ISDIR(unsigned short m) noexcept
{
    return (m & S_IFMT) == S_IFDIR;
}
#endif

std::optional<struct _stat> CreateStat(const char8_t* path, const std::span<wchar_t>& utf16PathBuffer)
{
    if (MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(path), -1, &utf16PathBuffer[0], static_cast<int>(utf16PathBuffer.size())) == 0)
    {
        return {};
    }

    struct _stat s{};
    if (_wstat(&utf16PathBuffer[0], &s) != 0)
    {
        return {};
    }

    return s;
}

bool InternalRecursiveDelete(const std::wstring_view& path)
{
    std::array<wchar_t, 2048> tempPathStr{};
    memcpy(&tempPathStr[0], path.data(), path.size() * 2);

    size_t pathLen = path.size();
    if (Path::IsDirectorySeparator(static_cast<char8_t>(path.back())))
    {
        tempPathStr[pathLen] = L'*';
        pathLen += 1;
    }
    else
    {
        tempPathStr[pathLen] = Path::DirectorySeparatorChar;
        tempPathStr[pathLen + 1] = L'*';
        pathLen += 2;
    }

    WIN32_FIND_DATAW findData;
    auto* const handle = FindFirstFileW(&tempPathStr[0], &findData);
    if (handle != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                // Ignore the . and ..
                if (findData.cFileName[0] == L'.' && (findData.cFileName[1] == L'\0' || (findData.cFileName[1] == L'.' && findData.cFileName[2] == L'\0')))
                {
                    continue;
                }

                const size_t fileNameLen = std::char_traits<wchar_t>::length(findData.cFileName);
                memcpy(&tempPathStr[pathLen - 1], findData.cFileName, fileNameLen * 2 + sizeof(findData.cFileName[0]));

                InternalRecursiveDelete({&tempPathStr[0], pathLen + fileNameLen - 1});
            }
            else
            {
                const size_t fileNameLen = std::char_traits<wchar_t>::length(findData.cFileName);
                memcpy(&tempPathStr[pathLen - 1], findData.cFileName, fileNameLen * 2 + sizeof(findData.cFileName[0]));

                _wremove(&tempPathStr[0]);
            }
        } while (FindNextFileW(handle, &findData) == TRUE);

        FindClose(handle);
    }

    return _wrmdir(path.data()) == 0;
}

}

bool Directory::Delete(const char8_t* path, bool recursive)
{
    std::array<wchar_t, 2048> utf16Path{};
    auto s = CreateStat(path, utf16Path);
    if (s.has_value() == false || S_ISDIR(s->st_mode) == false)
    {
        return false;
    }

    if (recursive)
    {
        return InternalRecursiveDelete(&utf16Path[0]);
    }

    return _wrmdir(&utf16Path[0]) == 0;
}

bool Directory::Exists(const char8_t* path)
{
    std::array<wchar_t, 2048> utf16Path{};
    auto s = CreateStat(path, utf16Path);
    if (s.has_value() == false || S_ISDIR(s->st_mode) == false)
    {
        return false;
    }

    return true;
}

std::vector<std::u8string> Directory::GetLogicalDrives()
{
    const auto driveFlags = ::GetLogicalDrives();

    std::vector<std::u8string> ret;
    char8_t root[] = u8"A:\\";
    for (auto d = driveFlags; d != 0; d >>= 1)
    {
        if ((d & 1) != 0)
        {
            ret.emplace_back(root, std::extent_v<decltype(root)> - 1);
        }

        ++root[0];
    }

    return ret;
}

bool Directory::Move(const char8_t* srcPath, const char8_t* destPath)
{
    std::array<wchar_t, 2048> utf16SrcPath{};
    auto s = CreateStat(srcPath, utf16SrcPath);
    if (s.has_value() == false || S_ISDIR(s->st_mode) == false)
    {
        return false;
    }

    std::array<wchar_t, 2048> utf16DestPath{};
    if (MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(destPath), -1, &utf16DestPath[0], static_cast<int>(utf16DestPath.size())) == 0)
    {
        return {};
    }

    return _wrename(&utf16SrcPath[0], &utf16DestPath[0]) == 0;
}

bool Directory::SetCurrentDirectory(const char8_t* path)
{
    std::array<wchar_t, 2048> utf16Path{};
    if (MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(path), -1, &utf16Path[0], utf16Path.size()) == 0)
    {
        return false;
    }

    return _wchdir(&utf16Path[0]) == 0;
}

std::optional<int32_t> Directory::GetCurrentDirectory(char8_t* destStr, int32_t destStrBufferLen)
{
    std::array<wchar_t, 2048> utf16Path{};
    if (GetCurrentDirectoryW(static_cast<DWORD>(utf16Path.size()), &utf16Path[0]) == 0)
    {
        return {};
    }

    const auto utf8PathLen = WideCharToMultiByte(CP_UTF8, 0, &utf16Path[0], -1, reinterpret_cast<char*>(destStr), destStrBufferLen, nullptr, nullptr) - 1;
    if (utf8PathLen == -1)
    {
        return {};
    }

    return utf8PathLen;
}

bool Directory::InternalCreateDirectory(const char8_t* path)
{
    std::array<wchar_t, 2048> utf16Path{};
    if (MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<const char*>(path), -1, &utf16Path[0], utf16Path.size() == 0))
    {
        return false;
    }

    return _wmkdir(&utf16Path[0]) == 0;
}

}