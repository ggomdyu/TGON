/**
 * @filename    Hash.h
 * @author      ggomdyu
 * @since       03/04/2017
 */

#pragma once
#include <cstddef>
#include <boost/predef/compiler.h>

#include "Core/Platform/Config.h"

namespace tgon
{
namespace hash
{

#if (__cplusplus == 201402L)
constexpr int32_t Hash::x65599Hash(const char* str)
{
    HashValue hashValue = 0;
    for (std::size_t i = 0; str[i] != '\0'; ++i)
    {
        hashValue = 65599 * hashValue + str[i];
    }

    return hashValue ^ (hashValue >> 16);
}
#elif (__cplusplus == 201103L)
// @brief   Generate x65599 hash by recursive.
constexpr int32_t x65599Hash(const char* str, int prevHashValue = 0)
{
    return (str[0] != '\0') ? 65599 * x65599Hash(&str[1]) + str[0] : prevHashValue ^ (prevHashValue >> 16);
}
#endif

} /* namespace hash */
} /* namespace tgon */
