/**
 * @filename    BaseTime.h
 * @author      ggomdyu
 * @since       05/15/2016
 * @desc        Set of Platform-agnostic Locale interface.
 */

#pragma once
#include <cstddef>

#include "Core/Platform/Config.h"

namespace tgon
{
namespace platform
{

/**
 * @brief                       Get the current language of OS.
 * @param [out] destBuffer      The destination of the string to be written.
 * @param [in] bufferLength     The length of buffer
 */
TGON_API void GetLanguage(char* destBuffer, std::size_t bufferLength);

template <std::size_t N>
inline void GetLanguage(char(&destBuffer)[N])
{
    GetLanguage(destBuffer, N);
}

} /* namespace platform */
} /* namespace tgon */