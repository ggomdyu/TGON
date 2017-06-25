/**
 * @filename    Hash.h
 * @author      ggomdyu
 * @since       03/04/2017
 */

#pragma once
#include "Core/Platform/Config.h"

#include <cstddef>

namespace tgon
{
namespace hash
{

using HashValue = std::size_t;

// @brief   Generate x65599 hash by recursive.
constexpr HashValue x65599Hash(const char* str, int prevHashValue = 0)
{
    return (str[0] != '\0') ? 65599 * x65599Hash(&str[1]) + str[0] : prevHashValue ^ (prevHashValue >> 16);
}

} /* namespace hash */
} /* namespace tgon */
