/**
 * @filename    Locale.h
 * @author      ggomdyu
 * @since       05/15/2016
 * @brief       Set of Platform-agnostic Locale interfaces.
 */

#pragma once
#include "Core/Platform/Config.h"

#include <cstdlib>
#include <cstdint>
#include <string>

namespace tgon
{
namespace core
{

/**
 * @brief                           Returns the current system language.
 * @param [out] destStr             The destination of the string to be written.
 * @param [in] destStrBufferBytes   The bytes length of buffer
 */
int32_t GetLanguage(char* destStr, std::size_t destStrBufferBytes);

/**
 * @brief                   Returns the current system language.
 * @param [out] destStr     The destination of the string to be written.
 */
template <std::size_t N>
inline int32_t GetLanguage(char(&destStr)[N])
{
    return GetLanguage(destStr, N);
}

/* @brief   Returns the current system language. */
std::string GetLanguage();

} /* namespace core */
} /* namespace tgon */