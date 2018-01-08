/**
* @filename    Encoding.h
* @author      ggomdyu
* @since       04/09/2017
*/

#pragma once
#include "Core/Platform/Config.h"

#include <string>
#include <cstdint>
#include <unicode/unistr.h>
#include <unicode/ucnv.h>

namespace tgon
{
namespace core
{

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
    template <typename _FromEncodingType, typename _ToEncodingType>
    static int32_t Convert(const char* srcStr, std::size_t srcStrLen, char* destStr, std::size_t destStrBufferSize)
    {
        return _FromEncodingType::Convert<_ToEncodingType>(srcStr, srcStrLen, destStr, destStrBufferSize);
    }

    template <typename _FromEncodingType, typename _ToEncodingType, std::size_t _DestStrBufferSize>
    static int32_t Convert(const char* srcStr, std::size_t srcStrLen, char(&destStr)[_DestStrBufferSize])
    {
        return _FromEncodingType::Convert<_ToEncodingType>(srcStr, srcStrLen, destStr, _DestStrBufferSize);
    }

    template <typename _FromEncodingType, typename _ToEncodingType, std::size_t _SrcStrBufferSize, std::size_t _DestStrBufferSize>
    static int32_t Convert(const char(&srcStr)[_SrcStrBufferSize], char(&destStr)[_DestStrBufferSize])
    {
        return _FromEncodingType::Convert<_ToEncodingType>(srcStr, _SrcStrBufferSize - 1, destStr, _DestStrBufferSize);
    }
};
class UTF8
{
public:
    template <typename _ToEncodingType>
    static int32_t Convert(const char* srcStr, std::size_t srcStrLen, char* destStr, std::size_t destStrBufferSize);
};

template <>
inline int32_t UTF8::Convert<UTF16LE>(const char* srcStr, std::size_t srcStrLen, char* destStr, std::size_t destStrBufferSize)
{
    UErrorCode errorCode;
    UConverter* conv = ucnv_open("UTF8", &errorCode);
    if (U_FAILURE(errorCode))
    {
        return false;
    }

    int32_t length = ucnv_toUChars(conv, reinterpret_cast<UChar*>(destStr), destStrBufferSize, srcStr, srcStrLen, &errorCode);
    if (U_FAILURE(errorCode))
    {
        return false;
    }
    
    ucnv_close(conv);
    return length;
}


class UTF16LE
{
public:
    template <typename _ToEncodingType>
    static int32_t Convert(const char* srcStr, std::size_t srcStrLen, char* destStr, std::size_t destStrBufferSize);
};

template <>
inline int32_t UTF16LE::Convert<UTF8>(const char* srcStr, std::size_t srcStrLen, char* destStr, std::size_t destStrBufferSize)
{
    UErrorCode errorCode;
    UConverter* conv = ucnv_open("UTF8", &errorCode);
    if (U_FAILURE(errorCode))
    {
        return false;
    }
 
    int32_t length = ucnv_fromUChars(conv, destStr, destStrBufferSize, reinterpret_cast<const UChar*>(srcStr), srcStrLen, &errorCode);
    if (U_FAILURE(errorCode))
    {
        return false;
    }

    ucnv_close(conv);
    return length;
}


/**
 * @brief               Converts UTF8 string to UTF16.
 * @param [in] src      The UTF8 string
 * @param [out] dest    A pointer of character array to be stored UTF16 string
 * @return              The length of converted string, or -1 on failure. 
 */
TGON_API int32_t ConvertUTF8ToUTF16(const char* src, char* dest);

} /* namespace core */
} /* namespace tgon */