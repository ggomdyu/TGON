/**
 * @filename    Encoding.inl
 * @author      ggomdyu
 * @since       02/20/2018
 */

#include <unicode/unistr.h>
#include <unicode/ucnv.h>

#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   pragma comment(lib, "icuucd.lib")
#endif

namespace tgon
{

template <typename _DerivedEncodingType>
inline int32_t Encoding<_DerivedEncodingType>::GetCharCount(const char* srcStr)
{
    return _DerivedEncodingType::GetCharCount(srcStr);
}

template<typename _DerivedEncodingType>
constexpr int32_t Encoding<_DerivedEncodingType>::GetMinCharSize() noexcept
{
    return _DerivedEncodingType::GetMinCharSize();
}

template<typename _DerivedEncodingType>
constexpr int32_t Encoding<_DerivedEncodingType>::GetMaxCharSize() noexcept
{
    return _DerivedEncodingType::GetMaxCharSize();
}

inline int32_t ASCII::GetCharCount(const char* srcStr)
{
    return std::strlen(srcStr);
}

constexpr int32_t ASCII::GetMinCharSize() noexcept
{
    return 1;
}

constexpr int32_t ASCII::GetMaxCharSize() noexcept
{
    return 1;
}

template <>
inline int32_t UTF8::Convert<UTF16LE>(const char* srcStr, std::size_t srcStrBytes, char* destStr, std::size_t destStrBufferSize)
{
    // UNIT_TEST: Is srcStr encoded by UTF-8?
    return 0;
/*
    UErrorCode errorCode = UErrorCode::U_ZERO_ERROR;
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
    return length;*/
}

constexpr int32_t UTF8::GetMinCharSize() noexcept
{
    return 1;
}

constexpr int32_t UTF8::GetMaxCharSize() noexcept
{
    return 3;
}

inline int32_t UTF8::GetCharCount(const char* srcStr)
{
    return int32_t();
}

template <>
inline int32_t UTF16LE::Convert<UTF8>(const char* srcStr, std::size_t srcStrBytes, char* destStr, std::size_t destStrBufferSize)
{
    // UNIT_TEST: Is srcStr encoded by UTF16LE?
    return 0;
   /* UErrorCode errorCode = UErrorCode::U_ZERO_ERROR;
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
    return bytes;*/
}

constexpr int32_t UTF16LE::GetMinCharSize() noexcept
{
    return 2;
}

constexpr int32_t UTF16LE::GetMaxCharSize() noexcept
{
    return 2;
}

constexpr int32_t UTF32::GetMinCharSize() noexcept
{
    return 4;
}

constexpr int32_t UTF32::GetMaxCharSize() noexcept
{
    return 4;
}

constexpr int32_t EUC_KR::GetMinCharSize() noexcept
{
    return 1;
}

constexpr int32_t EUC_KR::GetMaxCharSize() noexcept
{
    return 2;
}

constexpr int32_t EUC_JP::GetMinCharSize() noexcept
{
    return 1;
}

constexpr int32_t EUC_JP::GetMaxCharSize() noexcept
{
    return 3;
}

} /* namespace tgon */