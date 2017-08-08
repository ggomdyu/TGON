/**
 * @filename    Algorithm.h
 * @author      ggomdyu
 * @since       07/05/2016
 * @brief       Utility support for algorithm.
 */

#pragma once
#include <cstddef>

namespace tgon
{
namespace utility
{

#if (__cplusplus >= 201402L)
template <typename _CharType>
constexpr bool IsPalindrome(const _CharType* str, std::size_t length)
{
    std::size_t halfStrLength = length / 2;

    for (std::size_t i = 0; i < halfStrLength; ++i)
    {
        if (str[i] != str[length - i])
        {
            return false;
        }
    }
    return true;
}
#elif (__cplusplus == 201103L)
namespace detail
{
template <typename _CharType>
constexpr bool IsPalindromeImpl(const _CharType* str, std::size_t length, std::size_t offset)
{
    return (offset < length / 2) ? (str[offset] == str[length - offset - 1]) ? IsPalindromeImpl(str, length, offset + 1) : false : true;
}
} /* namespace detail */

template <typename _CharType>
constexpr bool IsPalindrome(const _CharType* str, std::size_t length)
{
    return detail::IsPalindromeImpl(str, length, 0);
}
#endif

template <typename _CharType, std::size_t N>
constexpr bool IsPalindrome(const _CharType(&str)[N]) noexcept
{
    return IsPalindrome(str, N - 1);
}

} /* namespace utility */
} /* namespace tgon */
