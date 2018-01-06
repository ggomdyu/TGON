/**
* @filename    Encoding.h
* @author      ggomdyu
* @since       04/09/2017
*/

#pragma once
#include "Core/Platform/Config.h"

class ASCII;
class EUC_KR;
class EUC_JP;
class EUC_CN;
class UTF7;
class UTF8;
class UTF16LE;
class UTF16BE;
class UTF32;

class Encoding
{
public:
    template <typename _SrcEncodingType, typename _DestEncodingType>
    static void Convert(char* srcStr)
    {

    }
};



#include <string>
#include <cstdint>

namespace tgon
{
namespace core
{

/**
 * @brief               Converts UTF8 string to UTF16.
 * @param [in] src      The UTF8 string
 * @param [out] dest    A pointer of character array to be stored UTF16 string
 * @return              The length of converted string, or -1 on failure. 
 */
TGON_API int32_t ConvertUTF8ToUTF16(const char* src, char* dest);

} /* namespace core */
} /* namespace tgon */