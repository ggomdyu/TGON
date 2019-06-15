/**
 * @file    Encoding.h
 * @author  ggomdyu
 * @since   04/09/2017
 */

#pragma once
#include <string>
#include <cstdint>
#include <cassert>
#include <unicode/unistr.h>
#include <unicode/utypes.h>
//#include <iconv.h>

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
    icu::UnicodeString sd;
   /* assert(srcStr != nullptr);
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

    iconv_close(cd);*/

    return true;//isConvertSucceed;
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
/**@section Enum */
private:
    enum BitsToHex
    {
        _00000000 = 0x0,
        _10000000 = 0x80,
        _11000000 = 0xC0,
        _11100000 = 0xE0,
        _11110000 = 0xF0,
        _11111000 = 0x7C,
        _00001111 = 0x0F,
        _00011111 = 0x1F,
        _00111111 = 0x3F,
    };

/**@section Variable */
public:
    static constexpr const char EncodingName[] = "UTF-8";
    static constexpr const int32_t MinCharSize = 1;
    static constexpr const int32_t MaxCharSize = 3;
    static constexpr const int32_t CodePage = 65001;
    static constexpr const bool IsSingleByte = false;

/**@section Method */
public:
    static constexpr int32_t GetCharCount(const char* str);
    static constexpr char32_t ToChar32(const char* str);
};
    
constexpr int32_t UTF8::GetCharCount(const char* str)
{
    if (str == nullptr)
    {
        return 0;
    }

    int32_t chCount = 0;
    
    while (str[0] != '\0')
    {
        if ( ( str[0] & BitsToHex::_10000000) == 0)
        {
            str += 1;
        }
        else if ((str[0] & BitsToHex::_11100000) == BitsToHex::_11000000)
        {
            str += 2;
        }
        else if ((str[0] & BitsToHex::_11110000) == BitsToHex::_11100000)
        {
            str += 3;
        }
        else if ((str[0] & BitsToHex::_11111000) == BitsToHex::_11110000)
        {
            str += 4;
        }
        else
        {
            str += 1;
        }
        
        ++chCount;
    }
    
    return chCount;
}

constexpr char32_t UTF8::ToChar32(const char* str)
{
    if ((str[0] & BitsToHex::_10000000) == 0)
    {
        return str[0];
    }
    else if ((str[0] & BitsToHex::_11100000) == BitsToHex::_11000000)
    {
        return ((str[0] & BitsToHex::_00011111) << 6) | (str[1] & BitsToHex::_00111111);
    }
    else if ((str[0] & BitsToHex::_11110000) == BitsToHex::_11100000)
    {
        return ((str[0] & BitsToHex::_00001111) << 12) | ((str[1] & BitsToHex::_00111111) << 6) | (str[2] & BitsToHex::_00111111);
    }
    
    return 0;
}

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
