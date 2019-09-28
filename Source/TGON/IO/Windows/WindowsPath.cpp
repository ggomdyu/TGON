#include "PrecompiledHeader.h"

#include <Windows.h>

#include "String/Encoding.h"

#include "../Path.h"

namespace tgon
{

thread_local extern std::array<wchar_t, 32767> g_tempUtf16Buffer;

int32_t Path::GetFullPath(const std::string_view& path, char* destStr, int32_t destStrBufferLen)
{
    const wchar_t* utf16Path = &g_tempUtf16Buffer[0];
    auto utf16PathBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(path.data()), static_cast<int32_t>(path.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size()));
    if (utf16PathBytes == -1)
    {
        return -1;
    }

    auto utf16PathLen = utf16PathBytes / 2;
    wchar_t* utf16FullPath = &g_tempUtf16Buffer[utf16PathLen + 1];
    auto utf16FullPathLen = GetFullPathNameW(utf16Path, static_cast<DWORD>(g_tempUtf16Buffer.size() - (utf16PathBytes + sizeof(wchar_t))), utf16FullPath, nullptr);
    if (utf16FullPathLen == 0)
    {
        return -1;
    }

    auto destStrLen = Encoding::Convert(Encoding::Unicode(), Encoding::UTF8(), reinterpret_cast<const std::byte*>(&utf16FullPath[0]), static_cast<int32_t>(utf16FullPathLen * 2), reinterpret_cast<std::byte*>(&destStr[0]), destStrBufferLen);
    if (destStrLen == -1)
    {
        return -1;
    }

    return static_cast<int32_t>(destStrLen);
}

int32_t Path::GetTempPath(char* destStr, int32_t destStrBufferLen)
{
    //GetTempPathW(destStr, destStrBufferLen);
    return -1;
}

gsl::span<const char> Path::GetInvalidFileNameChars() noexcept
{
    constexpr char invalidFileNameChars[] = {
        '\"', '<', '>', '|', '\0', static_cast<char>(1), static_cast<char>(2), static_cast<char>(3),
        static_cast<char>(4), static_cast<char>(5), static_cast<char>(6), static_cast<char>(7), static_cast<char>(8),
        static_cast<char>(9), static_cast<char>(10), static_cast<char>(11), static_cast<char>(12),
        static_cast<char>(13), static_cast<char>(14), static_cast<char>(15), static_cast<char>(16),
        static_cast<char>(17), static_cast<char>(18), static_cast<char>(19), static_cast<char>(20),
        static_cast<char>(21), static_cast<char>(22), static_cast<char>(23), static_cast<char>(24),
        static_cast<char>(25), static_cast<char>(26), static_cast<char>(27), static_cast<char>(28),
        static_cast<char>(29), static_cast<char>(30), static_cast<char>(31), ':', '*', '?', '\\', '/'
    };
    return gsl::span(invalidFileNameChars, std::extent_v<decltype(invalidFileNameChars)> - 1);
}

gsl::span<const char> Path::GetInvalidPathChars() noexcept
{
    constexpr char invalidPathChars[] = {
        '|', '\0', static_cast<char>(1), static_cast<char>(2), static_cast<char>(3), static_cast<char>(4),
        static_cast<char>(5), static_cast<char>(6), static_cast<char>(7), static_cast<char>(8), static_cast<char>(9),
        static_cast<char>(10), static_cast<char>(11), static_cast<char>(12), static_cast<char>(13),
        static_cast<char>(14), static_cast<char>(15), static_cast<char>(16), static_cast<char>(17),
        static_cast<char>(18), static_cast<char>(19), static_cast<char>(20), static_cast<char>(21),
        static_cast<char>(22), static_cast<char>(23), static_cast<char>(24), static_cast<char>(25),
        static_cast<char>(26), static_cast<char>(27), static_cast<char>(28), static_cast<char>(29),
        static_cast<char>(30), static_cast<char>(31)
    };
    return gsl::span(invalidPathChars, std::extent_v<decltype(invalidPathChars)> - 1);
}

} /* namespace tgon */
