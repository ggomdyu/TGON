/**
 * @filename    Hash.h
 * @author      ggomdyu
 * @since       03/04/2017
 */

#pragma once
#include <cstdint>
#include <cstddef>

namespace tgon
{
namespace hash
{

constexpr uint32_t x65599Hash(const char* str)
{
    uint32_t hashValue = 0;
    for (std::size_t i = 0; str[i] != '\0'; ++i)
    {
        hashValue = 65599 * hashValue + str[i];
    }

    return hashValue ^ (hashValue >> 16);
}

} /* namespace hash */
} /* namespace tgon */
