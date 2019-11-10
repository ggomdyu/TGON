#include "PrecompiledHeader.h"

#include <sys/stat.h>

#include "Platform/Windows/Windows.h"
#include "Misc/Algorithm.h"
#include "Text/Encoding.h"

#include "../File.h"
#include "../Path.h"
#include "../DirectoryInfo.h"
#include "../Directory.h"

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
    if (_wstat(reinterpret_cast<const wchar_t*>(g_tempUtf16Buffer.data()), &s) != 0)
    {
        return {};
    }

    return s;
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
        return RemoveDirectoryW(g_tempUtf16Buffer.data()) == TRUE;
    }
    else
    {
        // todo: impl
    }
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
    if (Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(destPath), static_cast<int32_t>(strlen(destPath)), reinterpret_cast<std::byte*>(utf16DestPath.data()), static_cast<int32_t>(utf16DestPath.size())) == -1)
    {
        return false;
    }

    return _wrename(reinterpret_cast<const wchar_t*>(utf16SrcPath.data()), reinterpret_cast<const wchar_t*>(utf16DestPath.data())) == 0;
}

int32_t Directory::GetCurrentDirectory(char* destStr, int32_t destStrBufferLen)
{
    auto utf16StrLen = GetCurrentDirectoryW(static_cast<DWORD>(g_tempUtf16Buffer.size()), g_tempUtf16Buffer.data());
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
