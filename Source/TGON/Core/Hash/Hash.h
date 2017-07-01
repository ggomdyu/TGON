/**
 * @filename    Hash.h
 * @author      ggomdyu
 * @since       03/04/2017
 */

#pragma once
#include <cstddef>

#include "Core/Platform/Config.h"

namespace tgon
{
namespace hash
{

using HashValue = uint32_t;

namespace detail
{
constexpr HashValue x65599HashImpl(const char* str, HashValue prevHashValue)
{
    return (str[0] != '\0') ? 65599 * x65599HashImpl(&str[1], 0) + str[0] : prevHashValue ^ (prevHashValue >> 16);
}
} /* namespace detail */

#if (__cplusplus == 201402L)
constexpr HashValue Hash::x65599Hash(const char* str)
{
    HashValue hashValue = 0;
    for (std::size_t i = 0; str[i] != '\0'; ++i)
    {
        hashValue = 65599 * hashValue + str[i];
    }

    return hashValue ^ (hashValue >> 16);
}
#elif (__cplusplus == 201103L)
constexpr HashValue x65599Hash(const char* str)
{
    return detail::x65599HashImpl(str, 0);
}
#endif

} /* namespace hash */
} /* namespace tgon */
