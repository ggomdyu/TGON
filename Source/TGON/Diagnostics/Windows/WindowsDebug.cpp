#include "PrecompiledHeader.h"

#include <array>

#include "Platform/Windows/Windows.h"
#include "Text/Encoding.h"

#include "../Debug.h"

namespace tgon
{

thread_local extern std::array<wchar_t, 32767> g_tempUtf16Buffer;

void Debug::Write(const std::string_view& message)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    auto utf16MessageBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(message.data()), static_cast<int32_t>(message.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size()));
    if (utf16MessageBytes == -1)
    {
        return;
    }

    int32_t utf16MessageLen = utf16MessageBytes / 2;

    std::lock_guard<std::recursive_mutex> lockGuard(m_mutex);
    for (int32_t i = 0; i < m_indentLevel; ++i)
    {
        g_tempUtf16Buffer[utf16MessageLen + i] = '\t';
    }

    g_tempUtf16Buffer[utf16MessageLen + m_indentLevel] = '\0';

    OutputDebugStringW(reinterpret_cast<const wchar_t*>(g_tempUtf16Buffer.data()));
#endif
}

void Debug::WriteLine(const std::string_view& message)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    auto utf16MessageBytes = Encoding::Convert(Encoding::UTF8(), Encoding::Unicode(), reinterpret_cast<const std::byte*>(message.data()), static_cast<int32_t>(message.size()), reinterpret_cast<std::byte*>(&g_tempUtf16Buffer[0]), static_cast<int32_t>(g_tempUtf16Buffer.size()));
    if (utf16MessageBytes == -1)
    {
        return;
    }

    int32_t utf16MessageLen = utf16MessageBytes / 2;

    std::lock_guard<std::recursive_mutex> lockGuard(m_mutex);
    for (int32_t i = 0; i < m_indentLevel; ++i)
    {
        g_tempUtf16Buffer[utf16MessageLen + i] = '\t';
    }
    g_tempUtf16Buffer[utf16MessageLen + m_indentLevel] = '\n';
    g_tempUtf16Buffer[utf16MessageLen + m_indentLevel + 1] = '\0';

    OutputDebugStringW(reinterpret_cast<const wchar_t*>(g_tempUtf16Buffer.data()));
#endif
}

void Debug::Assert(bool condition, const std::string_view& message, const std::string_view& detailMessage)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    if (condition)
    {
        return;
    }

    Fail(message, detailMessage);
#endif
}

} /* namespace tgon */
