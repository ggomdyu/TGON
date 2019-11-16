#include "PrecompiledHeader.h"

#include <algorithm>
#include <sstream>

#include "Debug.h"

namespace tgon
{

void Debug::Assert(bool condition)
{
    Assert(condition, {"", 0}, {"", 0});
}

void Debug::Assert(bool condition, const std::string_view& message)
{
    Assert(condition, message, {"", 0});
}

void Debug::Fail(const std::string_view& message)
{
    Fail(message, {"", 0});
}

void Debug::Fail(const std::string_view& message, const std::string_view& detailMessage)
{
#if defined(_DEBUG) || !defined(NDEBUG)
    std::stringstream ss;
    ss << "---- DEBUG ASSERTION FAILED ----\n---- Assert Short Message ----\n" << message << "\n---- Assert Long Message ----\n" << detailMessage << "\n";

    std::lock_guard<std::recursive_mutex> lockGuard(m_mutex);

    // Ignore the indent when printing the failure message
    auto prevIndentLevel = m_indentLevel;
    m_indentLevel = 0;
    {
        Write(ss.str());
    }
    m_indentLevel = prevIndentLevel;

    abort();
#endif
}

void Debug::SetIndentLevel(int32_t indentLevel) noexcept
{
#if defined(_DEBUG) || !defined(NDEBUG)
    std::lock_guard<std::recursive_mutex> lockGuard(m_mutex);
    m_indentLevel = std::max(indentLevel, 0);
#endif
}

int32_t Debug::GetIndentLevel() noexcept
{
    return m_indentLevel;
}

void Debug::Indent()
{
#if defined(_DEBUG) || !defined(NDEBUG)
    std::lock_guard<std::recursive_mutex> lockGuard(m_mutex);
    m_indentLevel += 1;
#endif
}

void Debug::Unindent()
{
#if defined(_DEBUG) || !defined(NDEBUG)
    std::lock_guard<std::recursive_mutex> lockGuard(m_mutex);
    m_indentLevel = std::max(m_indentLevel - 1, 0);
#endif
}

} /* namespace tgon */
