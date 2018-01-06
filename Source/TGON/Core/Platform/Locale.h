/**
 * @filename    Locale.h
 * @author      ggomdyu
 * @since       05/15/2016
 * @brief       Set of Platform-agnostic Locale interfaces.
 */

#pragma once
#include "Core/Platform/Config.h"

#include <cstddef>

namespace tgon
{
namespace core
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

} /* namespace core */
} /* namespace tgon */