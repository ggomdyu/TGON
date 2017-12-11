/**
 * @filename    Locale.h
 * @author      ggomdyu
 * @since       05/15/2016
 * @brief       Set of Platform-agnostic Locale interface.
 */

#pragma once
#include <cstddef>

#include "Core/Platform/Config.h"

namespace tgon
{
namespace platform
{

/**
 * @brief                           Get the current language of OS.
 * @param [out] destStr             The destination of the string to be written.
 * @param [in] destStrBufferSize    The length of buffer
 */
TGON_API void GetLanguage(char* destStr, std::size_t destStrBufferSize);

template <std::size_t N>
inline void GetLanguage(char(&destStr)[N])
{
    GetLanguage(destStr, N);
}

} /* namespace platform */
} /* namespace tgon */
