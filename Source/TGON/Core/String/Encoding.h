/**
 * @filename    Encoding.h
 * @author      ggomdyu
 * @since       04/09/2017
 */

#pragma once
#include <string>
#include <cstdint>

#include "EncodingFwd.h"

namespace tgon
{

template <typename _EncodingType>
constexpr bool IsASCIIEncoding = std::is_same<_EncodingType, >::value;

template <typename _EncodingType>
constexpr bool IsANSIEncoding = std::is_base_of<EUCEncoding<_EncodingType>, _EncodingType>::value;

template <typename _EncodingType>
constexpr bool IsUnicodeEncoding = std::is_base_of<UnicodeEncoding<_EncodingType>, _EncodingType>::value;


template <typename _DerivedEncodingType>
class Encoding
{
/* @section Public method */
public:
    /* @brief   Returns the length of string specified by srcStr. */
    static int32_t GetCharCount(const char* srcStr);
    
    /* @brief   Returns the minimum bytes per characters in codepage. */
    static constexpr int32_t GetMinCharSize() noexcept;

    /* @brief   Returns the maximum bytes per characters in codepage. */
    static constexpr int32_t GetMaxCharSize() noexcept;
};

class ASCII :
    public Encoding<ASCII>
{
/* @section Public variable */
public:
    static constexpr const char EncodingName[] = "ASCII";

/* @section Public method */
public:
    static int32_t GetCharCount(const char* srcStr);
    static constexpr int32_t GetMinCharSize() noexcept;
    static constexpr int32_t GetMaxCharSize() noexcept;
};

template <typename _DerivedEncodingType>
class ANSIEncoding :
    public Encoding<_DerivedEncodingType>
{
public:
    template <typename _ToEncodingType>
    static int32_t Convert(const char* srcStr, std::size_t srcStrBytes, char* destStr, std::size_t destStrBufferSize) = delete;
};

class EUC_KR :
    public ANSIEncoding<EUC_KR>
{
/* @section Public variable */
public:
    static constexpr const char EncodingName[] = "EUC-KR";

/* @section Public method */
public:
    static constexpr int32_t GetMinCharSize() noexcept;
    static constexpr int32_t GetMaxCharSize() noexcept;
};

class EUC_JP :
    public ANSIEncoding<EUC_JP>
{
/* @section Public variable */
public:
    static constexpr const char EncodingName[] = "EUC-JP";

public:
    static constexpr int32_t GetMinCharSize() noexcept;
    static constexpr int32_t GetMaxCharSize() noexcept;
};

template <typename _DerivedEncodingType>
class UnicodeEncoding :
    public Encoding<_DerivedEncodingType>
{
};

class UTF8 :
    public UnicodeEncoding<UTF8>
{
/* @section Public variable */
public:
    static constexpr const char EncodingName[] = "UTF-8";

/* @section Public method */
public:
    template <typename _ToEncodingType>
    static int32_t Convert(const char* srcStr, std::size_t srcStrBytes, char* destStr, std::size_t destStrBufferSize) = delete;
    static int32_t GetCharCount(const char* srcStr);
    static constexpr int32_t GetMinCharSize() noexcept;
    static constexpr int32_t GetMaxCharSize() noexcept;
};

class UTF16LE :
    public UnicodeEncoding<UTF16LE>
{
/* @section Public variable */
public:
    static constexpr const char EncodingName[] = "UTF16-LE";

/* @section Public method */
public:
    template <typename _ToEncodingType>
    static int32_t Convert(const char* srcStr, std::size_t srcStrBytes, char* destStr, std::size_t destStrBufferSize) = delete;
    static int32_t GetCharCount(const char* srcStr);
    static constexpr int32_t GetMinCharSize() noexcept;
    static constexpr int32_t GetMaxCharSize() noexcept;
};

class UTF32 :
    public UnicodeEncoding<UTF32>
{
/* @section Public variable */
public:
    static constexpr const char EncodingName[] = "UTF-32";

/* @section Public method */
public:
    template <typename _ToEncodingType>
    static int32_t Convert(const char* srcStr, std::size_t srcStrBytes, char* destStr, std::size_t destStrBufferSize) = delete;
    static int32_t GetCharCount(const char* srcStr);
    static constexpr int32_t GetMinCharSize() noexcept;
    static constexpr int32_t GetMaxCharSize() noexcept;
};

} /* namespace tgon */

#include "Encoding.inl"