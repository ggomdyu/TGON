#include "PrecompiledHeader.h"

#include <sys/stat.h>

#include "Platform/Windows/Windows.h"
#include "Text/Encoding.h"

#include "../DirectoryInfo.h"
#include "../Directory.h"
#include "../File.h"
#include "../Path.h"

namespace tgon
{

extern thread_local std::array<wchar_t, 16383> g_tempUtf16Buffer;

namespace
{

#if !defined(S_ISDIR)
constexpr bool S_ISDIR(unsigned short m) noexcept
{
    return (m & S_IFMT) == S_IFDIR;
}
#endif

std::optional<struct _stat> CreateStat(const char* path, const gsl::span<wchar_t>& utf16Buffer)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path), static_cast<int32_t>(strlen(path)), reinterpret_cast<std::byte*>(&utf16Buffer[0]), static_cast<int32_t>(utf16Buffer.size())) == -1)
    {
        return {};
    }

    struct _stat s;
    if (_wstat(reinterpret_cast<const wchar_t*>(&g_tempUtf16Buffer[0]), &s) != 0)
    {
        return {};
    }

    return s;
}

bool InternalRecursiveDelete(const std::wstring_view& path)
{
    std::array<wchar_t, 4096> tempPathStr{};
    memcpy(&tempPathStr[0], path.data(), path.size() * 2);

    size_t pathLen = path.size();
    if (Path::IsDirectorySeparator(path.back()))
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
    HANDLE handle = FindFirstFileW(reinterpret_cast<const wchar_t*>(&tempPathStr[0]), &findData);
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

                size_t fileNameLen = wcslen(findData.cFileName);
                memcpy(&tempPathStr[pathLen - 1], findData.cFileName, fileNameLen * 2 + sizeof(wchar_t));

                InternalRecursiveDelete({&tempPathStr[0], pathLen - 1 + fileNameLen});
            }
            else
            {
                size_t fileNameLen = wcslen(findData.cFileName);
                memcpy(&tempPathStr[pathLen - 1], findData.cFileName, fileNameLen * 2 + sizeof(wchar_t));

                _wremove(&tempPathStr[0]);
            }
        }
        while (FindNextFileW(handle, &findData) == TRUE);

        FindClose(handle);
    }

    return _wrmdir(path.data()) == 0;
}

} /* namespace */

bool Directory::Delete(const char* path, bool recursive)
{
    auto s = CreateStat(path, g_tempUtf16Buffer);
    if (s.has_value() == false || S_ISDIR(s->st_mode) == false)
    {
        return false;
    }

    if (recursive)
    {
        return InternalRecursiveDelete(&g_tempUtf16Buffer[0]);
    }

    return _wrmdir(&g_tempUtf16Buffer[0]) == 0;
}

bool Directory::Exists(const char* path)
{
    auto s = CreateStat(path, g_tempUtf16Buffer);
    if (s.has_value() == false || S_ISDIR(s->st_mode) == false)
    {
        return false;
    }

    return true;
}

std::vector<std::string> Directory::GetLogicalDrives()
{
    DWORD driveFlags = ::GetLogicalDrives();

    std::vector<std::string> ret;
    char root[] = "A:\\";
    for (DWORD d = driveFlags; d != 0; d >>= 1)
    {
        if ((d & 1) != 0)
        {
            ret.emplace_back(root, std::extent_v<decltype(root)> - 1);
        }

        ++root[0];
    }

    return ret;
}

bool Directory::Move(const char* srcPath, const char* destPath)
{
    gsl::span<wchar_t> utf16SrcPath(&g_tempUtf16Buffer[0], g_tempUtf16Buffer.size() / 2);
    auto s = CreateStat(srcPath, utf16SrcPath);
    if (s.has_value() == false || S_ISDIR(s->st_mode) == false)
    {
        return false;
    }

    gsl::span<wchar_t> utf16DestPath(&g_tempUtf16Buffer[g_tempUtf16Buffer.size() / 2], g_tempUtf16Buffer.size() / 2);
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(destPath), static_cast<int32_t>(strlen(destPath)), reinterpret_cast<std::byte*>(&utf16DestPath[0]), static_cast<int32_t>(utf16DestPath.size())) == -1)
    {
        return false;
    }

    return _wrename(reinterpret_cast<const wchar_t*>(utf16SrcPath.data()), reinterpret_cast<const wchar_t*>(utf16DestPath.data())) == 0;
}

bool Directory::SetCurrentDirectory(const char* path)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path), static_cast<int32_t>(strlen(path)), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return false;
    }

    return _wchdir(&g_tempUtf16Buffer[0]) == 0;
}

int32_t Directory::GetCurrentDirectory(char* destStr, int32_t destStrBufferLen)
{
    auto utf16StrLen = GetCurrentDirectoryW(static_cast<DWORD>(g_tempUtf16Buffer.size()), &g_tempUtf16Buffer[0]);
    return std::max(0, Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(utf16StrLen * 2), reinterpret_cast<std::byte*>(&destStr[0]), destStrBufferLen));
}

bool Directory::InternalCreateDirectory(const char* path)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path), static_cast<int32_t>(strlen(path)), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return false;
    }

    return _wmkdir(&g_tempUtf16Buffer[0]) == 0;
}

} /* namespace tgon */
