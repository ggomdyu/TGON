/**
 * @filename    Encoding.h
 * @author      ggomdyu
 * @since       04/09/2017
 */

#pragma once
#include "EncodingFwd.h"

#include "Core/Platform/Config.h"

#include <string>
#include <cstdint>

namespace tgon
{
namespace core
{

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
    static int32_t GetCharCount(const char* srcStr);
};

class UTF16LE :
    public UnicodeEncoding<UTF16LE>
{
public:
    static constexpr const char EncodingName[] = "UTF16-LE";

public:
    template <typename _ToEncodingType>
    static int32_t Convert(const char* srcStr, std::size_t srcStrLen, char* destStr, std::size_t destStrBufferSize) = delete;
    static int32_t GetCharCount(const char* srcStr);
};

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

#include "Encoding.inl"