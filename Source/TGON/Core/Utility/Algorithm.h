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
namespace core
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

} /* namespace core */
} /* namespace tgon */
