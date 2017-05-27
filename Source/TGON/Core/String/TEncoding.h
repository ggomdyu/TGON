/**
* @filename    TEncoding.h
* @author      ggomdyu
* @since       04/09/2017
*/

#pragma once
#include "Core/Platform/TConfig.h"

#include <string>
#include <cstdint>

namespace tgon {
namespace string {

/**
 * @brief               Converts UTF8 string to UTF16.
 * @param [in] src      The UTF8 string
 * @param [out] dest    A pointer of character array to be stored UTF16 string
 * @return              The byte count of converted string, or -1 on failure. 
 */
TGON_API int32_t ConvertUTF8ToUTF16(const char* src, char* dest);

} /* namespace string */
} /* namespace tgon */