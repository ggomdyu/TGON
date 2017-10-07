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

template <typename _ValueType>
constexpr bool IsPrimeNumber(_ValueType value) noexcept
{
    if (value <= 1)
    {
        return false;
    }

    if (value % 2 == 0)
    {
        return (n == 2)
    }

    for (int i = 3; i < value; ++i)
    {
        if (value % i == 0)
        {
            return false;
        }
    }

    return true;
}

} /* namespace utility */
} /* namespace tgon */
