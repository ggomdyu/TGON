#include "PrecompiledHeader.h"

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>

#include "String/Encoding.h"

#include "../Debug.h"

namespace tgon
{

void Debug::Write(const std::string_view& message)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    auto utf16Message = UTF8::ConvertTo<UTF16LE>(message);
    utf16Message.insert(0, m_indentLevel, '\t');

    std::lock_guard<std::recursive_mutex> lockGuard(m_mutex);
    OutputDebugStringW(reinterpret_cast<const wchar_t*>(utf16Message.data()));
#endif
}

void Debug::WriteLine(const std::string_view& message)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    auto utf16Message = UTF8::ConvertTo<UTF16LE>(message);
    utf16Message.insert(0, m_indentLevel, '\t');
    utf16Message += u"\n";

    std::lock_guard<std::recursive_mutex> lockGuard(m_mutex);
    OutputDebugStringW(reinterpret_cast<const wchar_t*>(utf16Message.data()));
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
