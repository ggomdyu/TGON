/**
 * @file    Debug.h
 * @author  ggomdyu
 * @since   04/01/2016
 * @brief   Set of platform agnostic debug interfaces.
 */

#pragma once
#include <cstdint>
#include <string_view>

#include "Platform/Config.h"

namespace tgon
{

class TGON_API Debug
{
/**@section Constructor */
private:
    Debug() = delete;
    ~Debug() = delete;

/**@section Method */
public:
    static void Assert(bool condition);
    static void Assert(bool condition, const std::string_view& message);
    static void Assert(bool condition, const std::string_view& message, const std::string_view& detailMessage);
    static void Fail(const std::string_view& message);
    static void Fail(const std::string_view& message, const std::string_view& detailMessage);
    static void Write(const std::string_view& message);
    static void WriteLine(const std::string_view& message);
    static void SetIndentLevel(int32_t indentLevel) noexcept;
    static int32_t GetIndentLevel() noexcept;
    static void Indent();
    static void Unindent();

/**@section Variable */
private:
    inline static int32_t m_indentLevel = 0;
};

} /* namespace tgon */
