#pragma once

#include <cstdlib>
#include <cstdint>
#include <string>

namespace tg
{

/**
 * @brief   Returns the current system language.
 * @param [out] destStr             The destination of the string to be written.
 * @param [in] destStrBufferLen    The bytes length of buffer
 */
int32_t GetLanguage(char* destStr, std::size_t destStrBufferLen);

/**@brief   Returns the current system language. */
std::string GetLanguage();

}
