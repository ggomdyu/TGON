#pragma once

#include "Encoding.h"
#include "Hash.h"

namespace tg
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
    [[nodiscard]] constexpr char32_t GetValue() const noexcept;
    [[nodiscard]] constexpr size_t GetHashCode() const noexcept;

private:
    constexpr char32_t ToChar32(const char* str);

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
    m_value(ToChar32(str))
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
    return X65599Hash(m_value);
}

constexpr char32_t UnicodeScalar::ToChar32(const char* str)
{
    enum BitsToHex
    {
        _10000000 = 0x80,
        _11000000 = 0xC0,
        _11100000 = 0xE0,
        _11110000 = 0xF0,
        _11111000 = 0x7C,
        _00000111 = 0x07,
        _00001111 = 0x0F,
        _00011111 = 0x1F,
        _00111111 = 0x3F,
    };

    if ((str[0] & BitsToHex::_10000000) == 0)
    {
        return str[0];
    }
    else if ((str[0] & BitsToHex::_11100000) == BitsToHex::_11000000)
    {
        return ((str[0] & BitsToHex::_00011111) << 6) | (str[1] & BitsToHex::_00111111);
    }
    else if ((str[0] & BitsToHex::_11110000) == BitsToHex::_11100000)
    {
        return ((str[0] & BitsToHex::_00001111) << 12) | ((str[1] & BitsToHex::_00111111) << 6) | (str[2] & BitsToHex::_00111111);
    }
    else if ((str[0] & BitsToHex::_11111000) == BitsToHex::_11110000)
    {
        return ((str[0] & BitsToHex::_00000111) << 18) | ((str[1] & BitsToHex::_00111111) << 12) | ((str[2] & BitsToHex::_00111111) << 6) | (str[3] & BitsToHex::_00111111);
    }
    
    return 0;
}

}

namespace std
{

template <>
struct hash<tg::UnicodeScalar>
{
/* @section Method */
public:
    size_t operator()(const tg::UnicodeScalar& rhs) const noexcept;
};

inline size_t hash<tg::UnicodeScalar>::operator()(const tg::UnicodeScalar& rhs) const noexcept
{
    return rhs.GetHashCode();
}
    
}
