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

using StringHash = std::size_t;

constexpr StringHash X65599Hash(const char* str)
{
    std::size_t hashValue = 0;
    for (std::size_t i = 0; str[i] != '\0'; ++i)
    {
        hashValue = 65599 * hashValue + str[i];
    }

    return hashValue ^ (hashValue >> 16);
}

} /* namespace tgon */
