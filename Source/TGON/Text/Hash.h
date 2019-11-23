/**
 * @file    Hash.h
 * @author  ggomdyu
 * @since   03/04/2017
 */

#pragma once
#include <cstdint>
#include <cstddef>

#include "Core/TypeTraits.h"

namespace tgon
{

template <typename _CharType, typename std::enable_if_t<IsChar<_CharType>>* = nullptr>
constexpr size_t X65599Hash(_CharType ch) noexcept
{
    return ch ^ (ch >> 16);
}
    
template <typename _CharType>
constexpr size_t X65599Hash(const _CharType* str) noexcept
{
    if (str == nullptr)
    {
        return 0;
    }
    
    size_t hashValue = 0;
    for (size_t i = 0; str[i] != 0; ++i)
    {
        hashValue = 65599 * hashValue + str[i];
    }

    return hashValue ^ (hashValue >> 16);
}

} /* namespace tgon */
