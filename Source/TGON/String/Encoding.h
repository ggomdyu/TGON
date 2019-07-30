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

namespace tgon
{

template <typename _FromEncodingType>
class Encoding
{
/**@section Type */
private:
    template <typename _ToEncodingType>
    using EncodeResultCharType =
        std::conditional_t<_ToEncodingType::MinCharSize == 1, char,
        std::conditional_t<_ToEncodingType::MinCharSize == 2, char16_t,
        std::conditional_t<_ToEncodingType::MinCharSize == 4, char32_t, char>>
    >;

/**@section Method */
public:
    /**
     * @brief   Converts a string from one encoding to another.
     * @param [in] srcStr               The source of _FromEncodingType.
     * @param [out] destStr             The output destination of _ToEncodingType.
     * @param [out] destStrBufferLen    The buffer length of output destination.
     * @return  Returns the bytes count of destStr if succeed, -1 otherwise.
     */
    template <typename _ToEncodingType, typename _SrcCharType, typename _DestCharType>
    static int32_t ConvertTo(const std::basic_string_view<_SrcCharType>& srcStr, _DestCharType* destStr, std::size_t destStrBufferLen);

    /**
     * @brief   Converts a string from one encoding to another.
     * @param [in] srcStr       The source of _FromEncodingType.
     * @param [out] destStr     The output destination of _ToEncodingType.
     * @return  Returns the bytes count of destStr if succeed, -1 otherwise.
     */
    template <typename _ToEncodingType, typename _SrcCharType, typename _DestCharType, std::size_t _DestCharBufferSize>
    static int32_t ConvertTo(const std::basic_string_view<_SrcCharType>& srcStr, _DestCharType(&destStr)[_DestCharBufferSize]);

    /**
     * @brief   Converts a string from one encoding to another.
     * @param [in] srcStr       The source of _FromEncodingType.
     * @param [out] destStr     The output destination of _ToEncodingType.
     * @return  Returns the bytes count of destStr if succeed, -1 otherwise.
     */
    template <typename _ToEncodingType, typename _SrcCharType>
    static std::basic_string<EncodeResultCharType<_ToEncodingType>> ConvertTo(const std::basic_string_view<_SrcCharType>& srcStr);
};

template <typename _FromEncodingType>
template <typename _ToEncodingType, typename _SrcCharType, typename _DestCharType>
inline int32_t Encoding<_FromEncodingType>::ConvertTo(const std::basic_string_view<_SrcCharType>& srcStr, _DestCharType* destStr, std::size_t destStrBufferLen)
{
    icu::UnicodeString ustr(reinterpret_cast<const char*>(srcStr.data()), static_cast<int32_t>(srcStr.length() * sizeof(_SrcCharType)), _FromEncodingType::EncodingName);

    int32_t encodedStrBytes = ustr.extract(0, ustr.length(), nullptr, _ToEncodingType::EncodingName);
    int32_t destStrBufferBytes = destStrBufferLen * sizeof(_DestCharType);
    if (encodedStrBytes + static_cast<int32_t>(sizeof(_DestCharType)) > destStrBufferBytes)
    {
        return -1;
    }

    ustr.extract(0, ustr.length(), reinterpret_cast<char*>(destStr), destStrBufferLen, _ToEncodingType::EncodingName);
    return encodedStrBytes;
}

template<typename _FromEncodingType>
template<typename _ToEncodingType, typename _SrcCharType, typename _DestCharType, std::size_t _DestCharBufferSize>
inline int32_t Encoding<_FromEncodingType>::ConvertTo(const std::basic_string_view<_SrcCharType>& srcStr, _DestCharType(&destStr)[_DestCharBufferSize])
{
    return ConvertTo<_ToEncodingType, _SrcCharType, _DestCharType>(srcStr, destStr, _DestCharBufferSize);
}

template<typename _FromEncodingType>
template<typename _ToEncodingType, typename _SrcCharType>
inline auto Encoding<_FromEncodingType>::ConvertTo(const std::basic_string_view<_SrcCharType>& srcStr) -> std::basic_string<EncodeResultCharType<_ToEncodingType>>
{
    icu::UnicodeString ustr(reinterpret_cast<const char*>(srcStr.data()), static_cast<int32_t>(srcStr.length() * sizeof(_SrcCharType)), _FromEncodingType::EncodingName);

    int32_t encodedStrBytes = ustr.extract(0, ustr.length(), nullptr, _ToEncodingType::EncodingName);

    std::basic_string<EncodeResultCharType<_ToEncodingType>> destStr;
    size_t destStrLen = encodedStrBytes / sizeof(Encoding<_FromEncodingType>);
    destStr.resize(destStrLen);

    ustr.extract(0, ustr.length(), reinterpret_cast<char*>(destStr.data()), destStrLen, _ToEncodingType::EncodingName);
    return destStr;
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
    static constexpr int32_t GetCharCount(const char* str);
    static constexpr char32_t ToChar32(const char* str);
};
    
constexpr int32_t UTF8::GetCharCount(const char* str)
{
    enum BitsToHex
    {
        _10000000 = 0x80,
        _11000000 = 0xC0,
        _11100000 = 0xE0,
        _11110000 = 0xF0,
        _11111000 = 0x7C,
    };

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
    enum BitsToHex
    {
        _10000000 = 0x80,
        _11000000 = 0xC0,
        _11100000 = 0xE0,
        _11110000 = 0xF0,
        _11111000 = 0x7C,
        _00000111 = 0x07,
        _00001111 = 0x0F,
        _00011111 = 0x1F,
        _00111111 = 0x3F,
    };

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
    else if ((str[0] & BitsToHex::_11111000) == BitsToHex::_11110000)
    {
        return ((str[0] & BitsToHex::_00000111) << 18) | ((str[1] & BitsToHex::_00111111) << 12) | ((str[2] & BitsToHex::_00111111) << 6) | (str[3] & BitsToHex::_00111111);
    }
    
    return 0;
}

class UTF16LE :
    public Encoding<UTF16LE>
{
/**@section Variable */
public:
    static constexpr const char EncodingName[] = "UTF16LE";
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
