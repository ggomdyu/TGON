/**
 * @filename    Encoding.h
 * @author      ggomdyu
 * @since       04/09/2017
 */

#pragma once
#include <string>
#include <cstdint>
#include <iconv.h>

namespace tgon
{

template <typename _FromEncodingType>
class Encoding
{
/* @section Public method */
public:
    template <typename _ToEncodingType, typename _CharType, typename _CharType2>
    static bool Convert(const _CharType* srcStr, std::size_t srcStrLen, _CharType2* destStr, std::size_t destStrBufferLen);
};

template <typename _FromEncodingType>
template <typename _ToEncodingType, typename _CharType, typename _CharType2>
inline bool Encoding<_FromEncodingType>::Convert(const _CharType* srcStr, std::size_t srcStrLen, _CharType2* destStr, std::size_t destStrBufferLen)
{
    assert(srcStr != nullptr);
    assert(destStr != nullptr);

    iconv_t cd = iconv_open(_ToEncodingType::EncodingName, _FromEncodingType::EncodingName);
    if (cd == iconv_t(-1))
    {
        return false;
    }

    size_t srcStrBytes = sizeof(_CharType) * (srcStrLen + 1);
    std::size_t destStrBufferBytes = sizeof(_CharType2) * (destStrBufferLen);

    bool isConvertSucceed = true;
    if (iconv(cd, (const char**)&srcStr, &srcStrBytes, (char**)&destStr, &destStrBufferBytes) == size_t(-1))
    {
        isConvertSucceed = false;
    }

    iconv_close(cd);

    return isConvertSucceed;
}

class ASCII :
    public Encoding<ASCII>
{
/* @section Public variable */
public:
    static constexpr const char EncodingName[] = "ASCII";
    static constexpr const int32_t MinCharSize = 1;
    static constexpr const int32_t MaxCharSize = 1;

/* @section Public method */
public:
    static int32_t GetCharCount(const char* srcStr);
};

class EUC_KR :
    public Encoding<EUC_KR>
{
/* @section Public variable */
public:
    static constexpr const char EncodingName[] = "EUC-KR";
    static constexpr const int32_t MinCharSize = 1;
    static constexpr const int32_t MaxCharSize = 2;
};

class EUC_JP :
    public Encoding<EUC_JP>
{
/* @section Public variable */
public:
    static constexpr const char EncodingName[] = "EUC-JP";
    static constexpr const int32_t MinCharSize = 1;
    static constexpr const int32_t MaxCharSize = 3;
};

template <typename _DerivedEncodingType>
class UnicodeEncoding :
    public Encoding<_DerivedEncodingType>
{
};

template <typename _EncodingType>
constexpr bool IsUnicodeEncoding = std::is_base_of<UnicodeEncoding<_EncodingType>, _EncodingType>::value;

class UTF8 :
    public UnicodeEncoding<UTF8>
{
/* @section Public variable */
public:
    static constexpr const char EncodingName[] = "UTF-8";
    static constexpr const int32_t MinCharSize = 1;
    static constexpr const int32_t MaxCharSize = 3;

/* @section Public method */
public:
    static int32_t GetCharCount(const char* srcStr);
};

class UTF16LE :
    public UnicodeEncoding<UTF16LE>
{
/* @section Public variable */
public:
    static constexpr const char EncodingName[] = "UTF-16LE";
    static constexpr const int32_t MinCharSize = 2;
    static constexpr const int32_t MaxCharSize = 2;

/* @section Public method */
public:
    static int32_t GetCharCount(const char* srcStr);
};

class UTF32 :
    public UnicodeEncoding<UTF32>
{
/* @section Public variable */
public:
    static constexpr const char EncodingName[] = "UTF-32";
    static constexpr const int32_t MinCharSize = 4;
    static constexpr const int32_t MaxCharSize = 4;

/* @section Public method */
public:
    static int32_t GetCharCount(const char* srcStr);
};

} /* namespace tgon */