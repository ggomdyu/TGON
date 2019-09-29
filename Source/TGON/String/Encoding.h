/**
 * @file    Encoding.h
 * @author  ggomdyu
 * @since   04/09/2017
 */

#pragma once
#include <string_view>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <gsl/span>

#include "Platform/Config.h"
#include "Core/NonCopyable.h"

struct UConverter;

namespace tgon
{

class TGON_API Encoding final :
    private NonCopyable
{
/**@section Constructor */
protected:
    Encoding() noexcept;
    explicit Encoding(const char* codePageName);
    explicit Encoding(int32_t codePage);
    explicit Encoding(UConverter* converter) noexcept;

public:
    Encoding(Encoding&& rhs) noexcept;

/**@section Destructor */
public:
    ~Encoding();
    
/**@section Operator */
public:
    Encoding& operator=(Encoding&& rhs) noexcept;
    bool operator==(const Encoding& rhs) const noexcept;
    bool operator!=(const Encoding& rhs) const noexcept;

/**@section Method */
public:                             
    static const Encoding& GetEncoding(int32_t codePage);
    static const Encoding& GetEncoding(const char* codePageName) noexcept(false);
    static std::vector<std::byte> Convert(const Encoding& srcEncoding, const Encoding& destEncoding, const std::byte* bytes, int32_t count);
    static int32_t Convert(const Encoding& srcEncoding, const Encoding& destEncoding, const std::byte* srcBytes, int32_t srcBytesCount, std::byte* destBytes, int32_t destBytesCount);
    static int32_t Convert(const Encoding& srcEncoding, const Encoding& destEncoding, const gsl::span<std::byte>& srcBytes, const gsl::span<std::byte>& destBytes);
    std::vector<char32_t> GetChars(const std::byte* bytes, int32_t count) const;
    std::vector<char32_t> GetChars(const gsl::span<std::byte>& bytes) const;
    int32_t GetCharCount(const std::byte* bytes, int32_t count) const;
    int32_t GetCharCount(const gsl::span<std::byte>& bytes) const;
    const std::string_view& GetEncodingName() const noexcept;
    int32_t GetCodePage() const noexcept;
    int32_t GetHashCode() const noexcept;
    static const Encoding& UTF8();
    static const Encoding& UTF32();
    static const Encoding& Unicode();
    static const Encoding& BigEndianUnicode();
    bool IsSingleByte() const noexcept;

private:
    static UConverter* CreateUConverter(const char* codePageName);
    static UConverter* CreateUConverter(int32_t codePage);
    int32_t GetMinCharByte() const noexcept;
    int32_t GetMaxCharByte() const noexcept;

/**@section Variable */
private:
    UConverter* m_converter;
    std::string_view m_encodingName;
    static std::unordered_map<int32_t, Encoding> m_encodingTable;
};

} /* namespace tgon */