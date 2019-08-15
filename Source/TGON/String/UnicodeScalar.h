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
/**@section Constructor */
public:
    constexpr UnicodeScalar(char value) noexcept;
    constexpr UnicodeScalar(char16_t value) noexcept;
    constexpr UnicodeScalar(char32_t value) noexcept;
    constexpr UnicodeScalar(wchar_t value) noexcept;
    constexpr UnicodeScalar(const char* str);

/**@section Operator */
public:
    constexpr operator char32_t() const noexcept;
    constexpr bool operator==(const UnicodeScalar& rhs) const noexcept;
    constexpr bool operator!=(const UnicodeScalar& rhs) const noexcept;
    constexpr bool operator>(const UnicodeScalar& rhs) const noexcept;
    constexpr bool operator>=(const UnicodeScalar& rhs) const noexcept;
    constexpr bool operator<(const UnicodeScalar& rhs) const noexcept;
    constexpr bool operator<=(const UnicodeScalar& rhs) const noexcept;

/**@section Method */
public:
    constexpr char32_t GetValue() const noexcept;
    constexpr size_t GetHashCode() const noexcept;

/**@section Variable */
private:
    char32_t m_value;
};

constexpr UnicodeScalar::UnicodeScalar(char value) noexcept :
    m_value(value)
{
}

constexpr UnicodeScalar::UnicodeScalar(char16_t value) noexcept :
    m_value(value)
{
}

constexpr UnicodeScalar::UnicodeScalar(char32_t value) noexcept :
    m_value(value)
{
}

constexpr UnicodeScalar::UnicodeScalar(wchar_t value) noexcept :
    m_value(value)
{
}

constexpr UnicodeScalar::UnicodeScalar(const char* str) :
    m_value(UTF8::ToChar32(str))
{
}

constexpr UnicodeScalar::operator char32_t() const noexcept
{
    return m_value;
}

constexpr bool UnicodeScalar::operator==(const UnicodeScalar& rhs) const noexcept
{
    return m_value == rhs.m_value;
}

constexpr bool UnicodeScalar::operator!=(const UnicodeScalar& rhs) const noexcept
{
    return m_value != rhs.m_value;
}

constexpr bool UnicodeScalar::operator>(const UnicodeScalar& rhs) const noexcept
{
    return m_value > rhs.m_value;
}

constexpr bool UnicodeScalar::operator>=(const UnicodeScalar& rhs) const noexcept
{
    return m_value >= rhs.m_value;
}

constexpr bool UnicodeScalar::operator<(const UnicodeScalar& rhs) const noexcept
{
    return m_value < rhs.m_value;
}

constexpr bool UnicodeScalar::operator<=(const UnicodeScalar& rhs) const noexcept
{
    return m_value <= rhs.m_value;
}

constexpr char32_t UnicodeScalar::GetValue() const noexcept
{
    return m_value;
}

constexpr size_t UnicodeScalar::GetHashCode() const noexcept
{
    return TGON_X65599(m_value);
}

}

namespace std
{

template<>
struct hash<tgon::UnicodeScalar>
{
/* @section Method */
public:
    size_t operator()(const tgon::UnicodeScalar& rhs) const noexcept;
};

inline size_t hash<tgon::UnicodeScalar>::operator()(const tgon::UnicodeScalar& rhs) const noexcept
{
    return rhs.GetHashCode();
}
    
} /* namespace std */
