/**
 * @file    Encoding.h
 * @author  ggomdyu
 * @since   04/09/2017
 */

#pragma once
#include <cstdint>

#include "Encoding.h"
#include "Hash.h"

namespace tgon
{

class UnicodeScalar
{
/**@section Method */
public:
    constexpr UnicodeScalar(char value) noexcept :
        m_value(value)
    {
    }

    constexpr UnicodeScalar(char16_t value) noexcept :
        m_value(value)
    {
    }

    constexpr UnicodeScalar(char32_t value) noexcept :
        m_value(value)
    {
    }
    
    constexpr UnicodeScalar(wchar_t value) noexcept :
        m_value(value)
    {
    }

    constexpr UnicodeScalar(const char* str) :
        m_value(UTF8::ToChar32(str))
    {
    }

/**@section Operator */
public:
    constexpr operator char32_t() noexcept
    {
        return m_value;
    }

/**@section Method */
public:
    constexpr char32_t GetValue() const noexcept
    {
        return m_value;
    }
    
    constexpr size_t GetHashCode() const noexcept
    {
        return TGON_X65599(m_value);
    }

/**@section Variable */
private:
    char32_t m_value;
};

} /* namespace tgon */
