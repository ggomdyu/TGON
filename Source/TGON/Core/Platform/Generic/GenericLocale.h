/**
 * @filename    GenericTime.h
 * @author      ggomdyu
 * @since       05/15/2016
 * @desc        Set of Platform agnostic interface.
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
void GetLanguage(char* destBuffer, std::size_t bufferLength);

template <std::size_t N>
inline void GetLanguage(char(&destBuffer)[N])
{
    GetLanguage(destBuffer, N);
}

} /* namespace tgon */
} /* namespace tgon */

