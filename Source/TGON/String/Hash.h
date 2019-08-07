/**
 * @file    Hash.h
 * @author  ggomdyu
 * @since   03/04/2017
 */

#pragma once
#include <cstdint>
#include <cstddef>

#include "Core/TypeTraits.h"

#ifdef _MSC_VER
#define TGON_X65599(str)\
    __pragma (warning(push))\
    __pragma (warning(disable: 4307))\
    X65599Hash(str)\
    __pragma (warning(pop))
#else
#define TGON_X65599(str) X65599Hash(str)
#endif

namespace tgon
{

template <typename _CharType, typename std::enable_if_t<IsCharValue<_CharType>>* = nullptr>
constexpr size_t X65599Hash(_CharType ch) noexcept
{
    return ch ^ (ch >> 16);
}
    
template <typename _CharType>
constexpr size_t X65599Hash(const _CharType* str) noexcept
{   
    std::size_t hashValue = 0;
    for (std::size_t i = 0; str[i] != 0; ++i)
    {
        hashValue = 65599 * hashValue + str[i];
    }

    return hashValue ^ (hashValue >> 16);
}

} /* namespace tgon */
