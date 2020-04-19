#include "PrecompiledHeader.h"

#include "Platform/Windows/Windows.h"

#include "../Path.h"

namespace tg
{

thread_local extern std::array<wchar_t, 16383> g_tempUtf16Buffer;

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

}
