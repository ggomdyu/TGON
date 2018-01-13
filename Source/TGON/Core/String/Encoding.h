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
class UTF8;
class UTF16LE;
template <typename _DerivedEncodingType>
class EUCEncoding;
template <typename _DerivedEncodingType>
class UnicodeEncoding;

template <typename _EncodingType>
constexpr bool IsUnicodeEncoding = std::is_base_of<UnicodeEncoding<_EncodingType>, _EncodingType>::value;
template <typename _EncodingType>
constexpr bool IsEUCEncoding = std::is_base_of<EUCEncoding<_EncodingType>, _EncodingType>::value;

template <typename _DerivedEncodingType>
class Encoding
{
public:
    static int32_t GetCharCount(const char* srcStr);
};

template <typename _DerivedEncodingType>
int32_t Encoding<_DerivedEncodingType>::GetCharCount(const char* srcStr)
{
    return _DerivedEncodingType::GetCharCount(srcStr);
}

template <typename _DerivedEncodingType>
class UnicodeEncoding :
    public Encoding<_DerivedEncodingType>
{
};

class UTF8 :
    public UnicodeEncoding<UTF8>
{
public:
    static constexpr const char EncodingName[] = "UTF-8";

public:
    template <typename _ToEncodingType>
    static int32_t Convert(const char* srcStr, std::size_t srcStrLen, char* destStr, std::size_t destStrBufferSize) = delete;
};

template <>
inline int32_t UTF8::Convert<UTF16LE>(const char* srcStr, std::size_t srcStrBytes, char* destStr, std::size_t destStrBufferSize)
{
    UErrorCode errorCode;
    UConverter* conv = ucnv_open("UTF8", &errorCode);
    if (U_FAILURE(errorCode))
    {
        return -1;
    }

    int32_t length = ucnv_toUChars(conv, reinterpret_cast<UChar*>(destStr), destStrBufferSize, srcStr, srcStrBytes, &errorCode);
    if (U_FAILURE(errorCode))
    {
        return -1;
    }

    ucnv_close(conv);
    return length;
}

class UTF16LE :
    public UnicodeEncoding<UTF16LE>
{
public:
    static constexpr const char EncodingName[] = "UTF16-LE";

public:
    template <typename _ToEncodingType>
    static int32_t Convert(const char* srcStr, std::size_t srcStrBytes, char* destStr, std::size_t destStrBufferSize) = delete;
};

template <>
inline int32_t UTF16LE::Convert<UTF8>(const char* srcStr, std::size_t srcStrBytes, char* destStr, std::size_t destStrBufferSize)
{
    UErrorCode errorCode = UErrorCode::U_ZERO_ERROR;
    UConverter* conv = ucnv_open("UTF8", &errorCode);
    if (U_FAILURE(errorCode))
    {
        return -1;
    }

    errorCode = UErrorCode::U_ZERO_ERROR;
    int32_t bytes = ucnv_fromUChars(conv, destStr, destStrBufferSize, reinterpret_cast<const UChar*>(srcStr), srcStrBytes, &errorCode);
    if (U_FAILURE(errorCode))
    {
        return -1;
    }

    ucnv_close(conv);
    return bytes;
}

template <typename _DerivedEncodingType>
class EUCEncoding :
    public Encoding<_DerivedEncodingType>
{
public:
    template <typename _ToEncodingType>
    static int32_t Convert(const char* srcStr, std::size_t srcStrBytes, char* destStr, std::size_t destStrBufferSize) = delete;
};

class EUC_KR :
    public EUCEncoding<EUC_KR>
{
public:
    static constexpr const char EncodingName[] = "EUC-KR";
};

class EUC_JP :
    public EUCEncoding<EUC_JP>
{
public:
    static constexpr const char EncodingName[] = "EUC-JP";
};

} /* namespace core */
} /* namespace tgon */