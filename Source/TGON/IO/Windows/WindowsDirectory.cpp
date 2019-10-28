#include "PrecompiledHeader.h"

#include <sys/stat.h>
#include <Windows.h>

#include "Misc/Algorithm.h"
#include "String/Encoding.h"

#include "../File.h"
#include "../Path.h"
#include "../Directory.h"
#include "../DirectoryInfo.h"

namespace tgon
{

extern thread_local std::array<wchar_t, 32767> g_tempUtf16Buffer;
extern thread_local std::array<char, 16384> g_tempUtf8Buffer;

namespace
{

#if !defined(S_ISDIR)
constexpr bool S_ISDIR(unsigned short m) noexcept
{
    return (m & S_IFMT) == S_IFDIR;
}
#endif

std::optional<struct _stat> CreateStat(const std::string_view& path)
{
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path.data()), static_cast<int32_t>(path.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size())) == -1)
    {
        return {};
    }

    struct _stat s;
    if (_wstat(reinterpret_cast<const wchar_t*>(g_tempUtf16Buffer.data()), &s) != 0)
    {
        return {};
    }

    return s;
}

std::vector<std::string> InternalEnumerateFileNames(const std::string_view& path, DWORD filterFileAttributes)
{
    int32_t utf16PathBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path.data()), static_cast<int32_t>(path.size() + 1), reinterpret_cast<std::byte*>(g_tempUtf16Buffer.data()), static_cast<int32_t>(sizeof(g_tempUtf16Buffer)));
    if (utf16PathBytes == -1)
    {
        return {};
    }

    int32_t utf16PathLen = (utf16PathBytes / 2) - 1;
    auto wildcard = gsl::make_span(L"/*");
    memcpy(&g_tempUtf16Buffer[utf16PathLen], wildcard.data(), wildcard.size());

    WIN32_FIND_DATAW findData;
    HANDLE handle = FindFirstFileW(reinterpret_cast<const wchar_t*>(g_tempUtf16Buffer.data()), &findData);
    if (handle == INVALID_HANDLE_VALUE)
    {
        return {};
    }

    std::vector<std::string> ret;

    do
    {
        bool isRelativeDirectory = findData.cFileName[0] == '.' && (findData.cFileName[1] == '\0' || (findData.cFileName[1] == '.' && findData.cFileName[2] == '\0'));
        if (!(findData.dwFileAttributes & filterFileAttributes) || isRelativeDirectory)
        {
            continue;
        }

        auto utf8FileNameBytes = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(findData.cFileName), static_cast<int32_t>(wcslen(findData.cFileName) * 2), reinterpret_cast<std::byte*>(&g_tempUtf8Buffer[0]), static_cast<int32_t>(g_tempUtf8Buffer.size()));
        if (utf8FileNameBytes == -1)
        {
            continue;
        }

        std::string str;
        if ((filterFileAttributes & FILE_ATTRIBUTE_ARCHIVE) == true)
        {
            str += path;
            str += Path::DirectorySeparatorChar;
        }
        str.append(&g_tempUtf8Buffer[0], utf8FileNameBytes);

        ret.push_back(std::move(str));
        
    } while (FindNextFileW(handle, &findData) == TRUE);

    FindClose(handle);
}

} /* namespace */

DirectoryInfo Directory::CreateDirectory(const std::string_view& path)
{
    auto s = CreateStat(path);
    if (s.has_value() == false || S_ISDIR(s->st_mode) == false)
    {
        _wmkdir(&g_tempUtf16Buffer[0]);
    }

    return DirectoryInfo(path);
}

bool Directory::Delete(const std::string_view& path, bool recursive)
{
    auto s = CreateStat(path);
    if (s.has_value() == false || S_ISDIR(s->st_mode) == false)
    {
        return false;
    }
    
    if (recursive)
    {
        return RemoveDirectoryW(g_tempUtf16Buffer.data()) == TRUE;
    }
    else
    {
        // todo: impl
    }
}

bool Directory::Exists(const std::string_view& path)
{
    auto s = CreateStat(path);
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

bool Directory::Move(const std::string_view& srcPath, const std::string_view& destPath)
{
    auto s = CreateStat(srcPath);
    if (s.has_value() == false || S_ISDIR(s->st_mode) == false)
    {
        return false;
    }

    wchar_t* utf16SrcPath = &g_tempUtf16Buffer[0];
    auto utf16SrcPathLen = wcslen(utf16SrcPath);

    wchar_t* utf16DestPath = &g_tempUtf16Buffer[utf16SrcPathLen + 1];
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(destPath.data()), static_cast<int32_t>(destPath.size()), reinterpret_cast<std::byte*>(utf16DestPath), static_cast<int32_t>(g_tempUtf16Buffer.size() - (utf16SrcPathLen + 1))) == -1)
    {
        return false;
    }

    return _wrename(reinterpret_cast<const wchar_t*>(utf16SrcPath), reinterpret_cast<const wchar_t*>(utf16DestPath)) == 0;
}

int32_t Directory::GetCurrentDirectory(char* destStr, int32_t destStrBufferLen)
{
    auto utf16StrLen = GetCurrentDirectoryW(static_cast<DWORD>(g_tempUtf16Buffer.size()), g_tempUtf16Buffer.data());
    if (utf16StrLen == 0)
    {
        return -1;
    }
    
    auto utf8StrLen = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(utf16StrLen * 2), reinterpret_cast<std::byte*>(&destStr[0]), destStrBufferLen);
    if (utf8StrLen >= 0)
    {
        return utf8StrLen;
    }

    return -1;
}

std::vector<std::string> Directory::GetDirectories(const std::string_view& path)
{
    return InternalEnumerateFileNames(path, FILE_ATTRIBUTE_DIRECTORY);
}

std::vector<std::string> Directory::GetFiles(const std::string_view& path)
{
    return InternalEnumerateFileNames(path, FILE_ATTRIBUTE_ARCHIVE);
}

} /* namespace tgon */
