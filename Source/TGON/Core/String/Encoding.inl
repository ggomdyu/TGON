/**
 * @filename    Encoding.inl
 * @author      ggomdyu
 * @since       02/20/2018
 */

#include <unicode/unistr.h>
#include <unicode/ucnv.h>

namespace tgon
{
namespace core
{

template <typename _DerivedEncodingType>
inline int32_t Encoding<_DerivedEncodingType>::GetCharCount(const char* srcStr)
{
    return _DerivedEncodingType::GetCharCount(srcStr);
}

template <>
inline int32_t UTF8::Convert<UTF16LE>(const char* srcStr, std::size_t srcStrLen, char* destStr, std::size_t destStrBufferSize)
{
    UErrorCode errorCode;
    UConverter* conv = ucnv_open("UTF8", &errorCode);
    if (U_FAILURE(errorCode))
    {
        return -1;
    }

    int32_t length = ucnv_toUChars(conv, reinterpret_cast<UChar*>(destStr), destStrBufferSize, srcStr, srcStrLen, &errorCode);
    if (U_FAILURE(errorCode))
    {
        return -1;
    }

    ucnv_close(conv);
    return length;
}

inline int32_t UTF8::GetCharCount(const char* srcStr)
{
    return int32_t();
}

template <>
inline int32_t UTF16LE::Convert<UTF8>(const char* srcStr, std::size_t srcStrLen, char* destStr, std::size_t destStrBufferSize)
{
    UErrorCode errorCode = UErrorCode::U_ZERO_ERROR;
    UConverter* conv = ucnv_open("UTF8", &errorCode);
    if (U_FAILURE(errorCode))
    {
        return -1;
    }

    errorCode = UErrorCode::U_ZERO_ERROR;
    int32_t bytes = ucnv_fromUChars(conv, destStr, destStrBufferSize, reinterpret_cast<const UChar*>(srcStr), srcStrLen, &errorCode);
    if (U_FAILURE(errorCode))
    {
        return -1;
    }

    ucnv_close(conv);
    return bytes;
}

} /* namespace core */
} /* namespace tgon */