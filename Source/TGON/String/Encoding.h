/**
 * @file    Encoding.h
 * @author  ggomdyu
 * @since   04/09/2017
 */

#pragma once
#include <string>
#include <cstdint>
#include <cassert>
#include <iconv.h>

namespace tgon
{

template <typename _FromEncodingType>
class Encoding
{
/**@section Method */
public:
    template <typename _ToEncodingType, typename _SrcCharType, typename _DestCharType>
    static bool ConvertTo(const std::basic_string_view<_SrcCharType>& srcStr, _DestCharType* destStr, std::size_t destStrBufferLen);
};

template <typename _FromEncodingType>
template <typename _ToEncodingType, typename _SrcCharType, typename _DestCharType>
inline bool Encoding<_FromEncodingType>::ConvertTo(const std::basic_string_view<_SrcCharType>& srcStr, _DestCharType* destStr, std::size_t destStrBufferLen)
{
    assert(srcStr != nullptr);
    assert(destStr != nullptr);

    iconv_t cd = iconv_open(_ToEncodingType::EncodingName, _FromEncodingType::EncodingName);
    if (cd == iconv_t(-1))
    {
        return false;
    }

    size_t srcStrBytes = sizeof(_SrcCharType) * (srcStr.length() + 1);
    std::size_t destStrBufferBytes = sizeof(_DestCharType) * (destStrBufferLen);

    bool isConvertSucceed = true;
    if (iconv(cd, (const char**)&srcStr.data(), &srcStrBytes, (char**)&destStr, &destStrBufferBytes) == size_t(-1))
    {
        isConvertSucceed = false;
    }

    iconv_close(cd);

    return isConvertSucceed;
}

class ASCII :
    public Encoding<ASCII>
{
/**@section Variable */
public:
    static constexpr const char EncodingName[] = "US-ASCII";
    static constexpr const int32_t MinCharSize = 1;
    static constexpr const int32_t MaxCharSize = 1;
    static constexpr const int32_t CodePage = 20127;
    static constexpr const bool IsSingleByte = true;

/**@section Method */
public:
    static int32_t GetCharCount(const char* str);
};

class UTF8 :
    public Encoding<UTF8>
{
/**@section Variable */
public:
    static constexpr const char EncodingName[] = "UTF-8";
    static constexpr const int32_t MinCharSize = 1;
    static constexpr const int32_t MaxCharSize = 3;
    static constexpr const int32_t CodePage = 65001;
    static constexpr const bool IsSingleByte = false;

/**@section Method */
public:
    static int32_t GetCharCount(const char* str);
};

class UTF16LE :
    public Encoding<UTF16LE>
{
/**@section Variable */
public:
    static constexpr const char EncodingName[] = "UTF-16LE";
    static constexpr const int32_t MinCharSize = 2;
    static constexpr const int32_t MaxCharSize = 2;
    static constexpr const int32_t CodePage = 1200;
    static constexpr const bool IsSingleByte = false;

/**@section Method */
public:
    static int32_t GetCharCount(const char* str);
};

class UTF32 :
    public Encoding<UTF32>
{
/**@section Variable */
public:
    static constexpr const char EncodingName[] = "UTF-32";
    static constexpr const int32_t MinCharSize = 4;
    static constexpr const int32_t MaxCharSize = 4;
    static constexpr const int32_t CodePage = 12000;
    static constexpr const bool IsSingleByte = false;

/**@section Method */
public:
    static int32_t GetCharCount(const char* srcStr);
};

} /* namespace tgon */