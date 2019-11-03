#include "PrecompiledHeader.h"

#include <ucnv_io.h>
#include <ucnv_bld.h>
#include <unicode/ucnv.h>
#include <unicode/unistr.h>
#include <unicode/utypes.h>

#include "Encoding.h"

extern const UConverterSharedData* getAlgorithmicTypeFromName(const char* realName);
extern const UConverterSharedData* getAlgorithmicTypeFromCodePage(int32_t codePage);

namespace tgon
{

std::unordered_map<int32_t, Encoding> Encoding::m_encodingTable;

Encoding::Encoding() noexcept :
    m_converter(nullptr)
{
}

Encoding::Encoding(Encoding&& rhs) noexcept :
    m_converter(rhs.m_converter),
    m_encodingName(rhs.m_encodingName)
{
    rhs.m_converter = nullptr;
}

Encoding::Encoding(const char* codePageName) :
    Encoding(CreateUConverter(codePageName))
{
}

Encoding::Encoding(int32_t codePage) :
    Encoding(CreateUConverter(codePage))
{
}

Encoding::Encoding(UConverter* converter) noexcept :
    m_converter(converter),
    m_encodingName(m_converter->sharedData->staticData->name)
{
}

Encoding::~Encoding()
{
    if (m_converter != nullptr)
    {       
        ucnv_close(m_converter);
        m_converter = nullptr;
    }
}

Encoding& Encoding::operator=(Encoding&& rhs) noexcept
{
    m_converter = rhs.m_converter;
    m_encodingName = rhs.m_encodingName;

    rhs.m_converter = nullptr;

    return *this;
}

bool Encoding::operator==(const Encoding& rhs) const noexcept
{
    return m_converter == rhs.m_converter;
}

bool Encoding::operator!=(const Encoding& rhs) const noexcept
{
    return !operator==(rhs);
}

const Encoding& Encoding::GetEncoding(int32_t codePage)
{
    constexpr int32_t IBM_UTF8_CCSID = 1208;
    constexpr int32_t IBM_UTF16LE_CCSID = 1202;
    constexpr int32_t IBM_UTF16BE_CCSID = 1200;
    constexpr int32_t IBM_UTF32LE_CCSID = 1236;
    switch (codePage)
    {
    case IBM_UTF8_CCSID:
        return UTF8();

    case IBM_UTF16LE_CCSID:
        return Unicode();

    case IBM_UTF16BE_CCSID:
        return BigEndianUnicode();

    case IBM_UTF32LE_CCSID:
        return UTF32();
    }

    auto iter = m_encodingTable.find(codePage);
    if (iter == m_encodingTable.end())
    {
        iter = m_encodingTable.insert(iter, {codePage, Encoding(codePage)});
    }

    return iter->second;
}

const Encoding& Encoding::GetEncoding(const char* codePageName) noexcept(false)
{
    UConverterLoadArgs converterLoadArgs {};
    converterLoadArgs.name = codePageName;

    auto converterSharedData = getAlgorithmicTypeFromName(codePageName);
    if (converterSharedData == nullptr)
    {
        throw std::runtime_error("Can't found the code page name.");
    }

    return GetEncoding(converterSharedData->staticData->codepage);
}

std::vector<std::byte> Encoding::Convert(const Encoding& srcEncoding, const Encoding& destEncoding, const std::byte* bytes, int32_t count)
{
    UErrorCode status = U_ZERO_ERROR;
    icu::UnicodeString ustr(reinterpret_cast<const char*>(bytes), count, srcEncoding.m_converter, status);
    if (U_FAILURE(status))
    {
        return {};
    }

    int32_t encodedStrBytes = ustr.extract(nullptr, 0, destEncoding.m_converter, status);

    std::vector<std::byte> ret(encodedStrBytes);
    status = U_ZERO_ERROR;
    ustr.extract(reinterpret_cast<char*>(&ret[0]), static_cast<int32_t>(ret.size()), destEncoding.m_converter, status);

    return ret;
}

int32_t Encoding::Convert(const Encoding& srcEncoding, const Encoding& destEncoding, const std::byte* srcBytes, int32_t srcBytesCount, std::byte* destBytes, int32_t destBytesCount)
{
    UErrorCode status = U_ZERO_ERROR;
    icu::UnicodeString ustr(reinterpret_cast<const char*>(srcBytes), srcBytesCount, srcEncoding.m_converter, status);
    if (U_FAILURE(status))
    {
        return -1;
    }

    int32_t encodedStrBytes = ustr.extract(nullptr, 0, destEncoding.m_converter, status);
    if (encodedStrBytes > destBytesCount)
    {
        return -1;
    }

    status = U_ZERO_ERROR;
    ustr.extract(reinterpret_cast<char*>(&destBytes[0]), destBytesCount, destEncoding.m_converter, status);

    return encodedStrBytes;
}

int32_t Encoding::Convert(const Encoding& srcEncoding, const Encoding& destEncoding, const gsl::span<std::byte>& srcBytes, const gsl::span<std::byte>& destBytes)
{
    return Convert(srcEncoding, destEncoding, &srcBytes[0], static_cast<int32_t>(srcBytes.size()), &destBytes[0], static_cast<int32_t>(destBytes.size()));
}

std::vector<char32_t> Encoding::GetChars(const std::byte* bytes, int32_t count) const
{
    std::vector<char32_t> ret;

    UErrorCode status = U_ZERO_ERROR;
    auto currIter = reinterpret_cast<const char*>(&bytes[0]);
    auto endIter = reinterpret_cast<const char*>(bytes + count);
    while (currIter < endIter)
    {
        auto ch = ucnv_getNextUChar(m_converter, &currIter, currIter + count, &status);
        if (U_FAILURE(status))
        {
            return {};
        }

        if (ch == 0)
        {
            break;
        }

        ret.push_back(static_cast<char32_t>(ch));
    }

    return ret;
}

std::vector<char32_t> Encoding::GetChars(const gsl::span<std::byte>& bytes) const
{
    return GetChars(&bytes[0], static_cast<int32_t>(bytes.size()));
}

int32_t Encoding::GetCharCount(const std::byte* bytes, int32_t count) const
{
    int32_t ret = 0;

    UErrorCode status = U_ZERO_ERROR;
    auto currIter = reinterpret_cast<const char*>(&bytes[0]);
    auto endIter = reinterpret_cast<const char*>(bytes + count);
    while (currIter < endIter)
    {
        auto ch = ucnv_getNextUChar(m_converter, &currIter, currIter + count, &status);
        if (U_FAILURE(status))
        {
            return -1;
        }

        if (ch == 0)
        {
            break;
        }

        ++ret;
    }

    return ret;
}

int32_t Encoding::GetCharCount(const gsl::span<std::byte>& bytes) const
{
    return GetCharCount(&bytes[0], static_cast<int32_t>(bytes.size()));
}

const std::string_view& Encoding::GetEncodingName() const noexcept
{
    return m_encodingName;
}

int32_t Encoding::GetCodePage() const noexcept
{
    return m_converter->sharedData->staticData->codepage;
}

uint32_t Encoding::GetHashCode() const noexcept
{
    return static_cast<uint32_t>(m_converter->sharedData->staticData->codepage);
}

const Encoding& Encoding::UTF8()
{
    static Encoding encoding("UTF8");
    return encoding;
}

const Encoding& Encoding::Unicode()
{
    static Encoding encoding("UTF16LE");
    return encoding;
}

const Encoding& Encoding::BigEndianUnicode()
{
    static Encoding encoding("UTF16BE");
    return encoding;
}

const Encoding& Encoding::UTF32()
{
    static Encoding encoding("UTF32");
    return encoding;
}

bool Encoding::IsSingleByte() const noexcept
{
    return this->GetMinCharByte() == 1 && this->GetMaxCharByte() == 1;
}

UConverter* Encoding::CreateUConverter(const char* codePageName)
{
    UErrorCode status = U_ZERO_ERROR;
    UConverter* converter = ucnv_open(codePageName, &status);
    if (U_FAILURE(status))
    {
        return nullptr;
    }

    return converter;
}

UConverter* Encoding::CreateUConverter(int32_t codePage)
{
    auto converterSharedData = getAlgorithmicTypeFromCodePage(codePage);
    if (converterSharedData == nullptr)
    {
        return nullptr;
    }

    UErrorCode status = U_ZERO_ERROR;
    UConverter* converter = ucnv_open(converterSharedData->staticData->name, &status);
    if (U_FAILURE(status))
    {
        return nullptr;
    }

    return converter;
}

int32_t Encoding::GetMinCharByte() const noexcept
{
    return m_converter->sharedData->staticData->minBytesPerChar;
}

int32_t Encoding::GetMaxCharByte() const noexcept
{
    return m_converter->sharedData->staticData->maxBytesPerChar;
}

} /* namespace tgon */
