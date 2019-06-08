/**
 * @file    Hash.h
 * @author  ggomdyu
 * @since   03/04/2017
 */

#pragma once
#include <cstdint>
#include <cstddef>
#include <boost/functional/hash.hpp>

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

constexpr size_t X65599Hash(const char* str) noexcept
{   
    std::size_t hashValue = 0;
    for (std::size_t i = 0; str[i] != '\0'; ++i)
    {
        hashValue = 65599 * hashValue + str[i];
    }

    return hashValue ^ (hashValue >> 16);
}

constexpr size_t X65599Hash(const wchar_t* str) noexcept
{
    std::size_t hashValue = 0;
    for (std::size_t i = 0; str[i] != L'\0'; ++i)
    {
        hashValue = 65599 * hashValue + str[i];
    }

    return hashValue ^ (hashValue >> 16);
}

} /* namespace tgon */