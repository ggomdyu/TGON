/**
 * @file    StringHash.h
 * @author  ggomdyu
 * @date    09/25/2018
 */

#pragma once
#include <string>

#include "Core/TypeTraits.h"

#include "Hash.h"
#include "FixedString.h"

namespace tgon
{

template <typename _StringType>
class BasicStringHash
{
/**@section Type */
public:
    using StringType = std::conditional_t<IsCharPointer<_StringType>, std::string_view, _StringType>;
    using ValueType = std::remove_reference_t<decltype(StringType("")[0])>;
    using HashCodeType = decltype(X65599Hash(""));

/**@section Constructor */
public:
    constexpr BasicStringHash() noexcept = default;
    template <typename _StringType2>
    constexpr BasicStringHash(_StringType2&& str) noexcept;

/**@section Operator */
public:
    template <typename _StringType2>
    constexpr bool operator==(const BasicStringHash<_StringType2>& rhs) const noexcept;
    template <typename _StringType2>
    constexpr bool operator!=(const BasicStringHash<_StringType2>& rhs) const noexcept;
    constexpr ValueType& operator[](int32_t index) noexcept;
    constexpr ValueType operator[](int32_t index) const noexcept;

/**@section Method */
public:
    constexpr HashCodeType GetHashCode() const noexcept;
    //template <int32_t _CharBufferSize2>
    //int32_t CompareTo(const BasicFixedString<ValueType, _CharBufferSize2, _StringTraitsType>& str) const;
    //int32_t CompareTo(const std::basic_string_view<ValueType>& str) const;
    //int32_t IndexOf(const std::basic_string_view<ValueType>& str, int32_t startIndex = 0) const;
    //int32_t IndexOf(ValueType ch, int32_t startIndex = 0) const;
    //template <typename _PredicateType>
    //int32_t IndexOfAny(const _PredicateType& predicate, int32_t startIndex = 0) const;
    //int32_t LastIndexOf(const std::basic_string_view<ValueType>& str) const;
    //int32_t LastIndexOf(const std::basic_string_view<ValueType>& str, int32_t startIndex = 0) const;
    //int32_t LastIndexOf(ValueType ch) const;
    //int32_t LastIndexOf(ValueType ch, int32_t startIndex) const;
    //template <typename _PredicateType>
    //int32_t LastIndexOfAny(const _PredicateType& predicate) const;
    //template <typename _PredicateType>
    //int32_t LastIndexOfAny(const _PredicateType& predicate, int32_t startIndex) const;
    constexpr const ValueType* Data() const noexcept;
    constexpr const int32_t Length() const noexcept;
    //IteratorType Begin() noexcept;
    //IteratorType End() noexcept;
    //ConstIteratorType CBegin() const noexcept;
    //ConstIteratorType CEnd() const noexcept;

/**@section Variable */
public:
    StringType m_str;
    HashCodeType m_hashCode = 0;
};

namespace detail
{

template <typename>
struct IsBasicStringHash : std::false_type {};

template <typename _StringType>
struct IsBasicStringHash<BasicStringHash<_StringType>> : std::true_type {};

} /* namespace detail */

template <typename _Type>
constexpr bool IsBasicStringHash = detail::IsBasicStringHash<_Type>::value;

template <typename _StringType>
template <typename _StringType2>
constexpr BasicStringHash<_StringType>::BasicStringHash(_StringType2&& str) noexcept :
    m_str([&]()
    {
        if constexpr (IsBasicStringHash<std::remove_reference_t<_StringType2>>)
        {
            if constexpr (std::is_same_v<_StringType, std::remove_reference_t<_StringType2>>)
            {
                return std::forward<_StringType2>(str.m_str);
            }
            else
            {
                return StringType(str.Data(), str.Length());
            }
        }
        else
        {
            return std::forward<_StringType2>(str);
        }
    } ()),
    m_hashCode([&]()
    {
        if constexpr (IsBasicStringHash<std::remove_reference_t<_StringType2>>)
        {
            return str.GetHashCode();
        }
        else
        {
            return X65599Hash(this->Data());
        }
    } ())
{
}

template <typename _StringType>
template <typename _StringType2>
constexpr bool BasicStringHash<_StringType>::operator==(const BasicStringHash<_StringType2>& rhs) const noexcept
{
    return m_str == rhs.m_str;
}

template <typename _StringType>
template <typename _StringType2>
constexpr bool BasicStringHash<_StringType>::operator!=(const BasicStringHash<_StringType2>& rhs) const noexcept
{
    return m_str != rhs.m_str;
}

template<typename _StringType>
constexpr typename BasicStringHash<_StringType>::ValueType& BasicStringHash<_StringType>::operator[](int32_t index) noexcept
{
    return m_str[index];
}

template<typename _StringType>
constexpr typename BasicStringHash<_StringType>::ValueType BasicStringHash<_StringType>::operator[](int32_t index) const noexcept
{
    return m_str[index];
}

template<typename _StringType>
constexpr typename BasicStringHash<_StringType>::HashCodeType BasicStringHash<_StringType>::GetHashCode() const noexcept
{
    return m_hashCode;
}

template<typename _StringType>
constexpr const typename BasicStringHash<_StringType>::ValueType* BasicStringHash<_StringType>::Data() const noexcept
{
    if constexpr (IsBasicString<StringType> || IsBasicStringView<StringType>)
    {
        return m_str.data();
    }
    else
    {
        return m_str.Data();
    }
}

template <typename _StringType>
constexpr const int32_t BasicStringHash<_StringType>::Length() const noexcept
{
    if constexpr (IsBasicString<StringType> || IsBasicStringView<StringType>)
    {
        return m_str.length();
    }
    else
    {
        return m_str.Length();
    }
}

using StringHash = BasicStringHash<std::string>;
using StringViewHash = BasicStringHash<std::string_view>;
using FixedString8Hash = BasicStringHash<FixedString8>;
using FixedString16Hash = BasicStringHash<FixedString16>;
using FixedString32Hash = BasicStringHash<FixedString32>;
using FixedString64Hash = BasicStringHash<FixedString64>;
using FixedString128Hash = BasicStringHash<FixedString128>;
using FixedString256Hash = BasicStringHash<FixedString256>;
using FixedString512Hash = BasicStringHash<FixedString512>;
using FixedString1024Hash = BasicStringHash<FixedString1024>;
using FixedString2048Hash = BasicStringHash<FixedString2048>;
using FixedString4096Hash = BasicStringHash<FixedString4096>;
using FixedString8192Hash = BasicStringHash<FixedString8192>;
    
using WStringHash = BasicStringHash<std::wstring>;
using WStringViewHash = BasicStringHash<std::wstring_view>;
using WFixedString8Hash = BasicStringHash<WFixedString8>;
using WFixedString16Hash = BasicStringHash<WFixedString16>;
using WFixedString32Hash = BasicStringHash<WFixedString32>;
using WFixedString64Hash = BasicStringHash<WFixedString64>;
using WFixedString128Hash = BasicStringHash<WFixedString128>;
using WFixedString256Hash = BasicStringHash<WFixedString256>;
using WFixedString512Hash = BasicStringHash<WFixedString512>;
using WFixedString1024Hash = BasicStringHash<WFixedString1024>;
using WFixedString2048Hash = BasicStringHash<WFixedString2048>;
using WFixedString4096Hash = BasicStringHash<WFixedString4096>;
using WFixedString8192Hash = BasicStringHash<WFixedString8192>;

using U16StringHash = BasicStringHash<std::u16string>;
using U16StringViewHash = BasicStringHash<std::u16string_view>;
using U16FixedString8Hash = BasicStringHash<U16FixedString8>;
using U16FixedString16Hash = BasicStringHash<U16FixedString16>;
using U16FixedString32Hash = BasicStringHash<U16FixedString32>;
using U16FixedString64Hash = BasicStringHash<U16FixedString64>;
using U16FixedString128Hash = BasicStringHash<U16FixedString128>;
using U16FixedString256Hash = BasicStringHash<U16FixedString256>;
using U16FixedString512Hash = BasicStringHash<U16FixedString512>;
using U16FixedString1024Hash = BasicStringHash<U16FixedString1024>;
using U16FixedString2048Hash = BasicStringHash<U16FixedString2048>;
using U16FixedString4096Hash = BasicStringHash<U16FixedString4096>;
using U16FixedString8192Hash = BasicStringHash<U16FixedString8192>;

using U32StringHash = BasicStringHash<std::u32string>;
using U32StringViewHash = BasicStringHash<std::u32string_view>;
using U32FixedString8Hash = BasicStringHash<U32FixedString8>;
using U32FixedString16Hash = BasicStringHash<U32FixedString16>;
using U32FixedString32Hash = BasicStringHash<U32FixedString32>;
using U32FixedString64Hash = BasicStringHash<U32FixedString64>;
using U32FixedString128Hash = BasicStringHash<U32FixedString128>;
using U32FixedString256Hash = BasicStringHash<U32FixedString256>;
using U32FixedString512Hash = BasicStringHash<U32FixedString512>;
using U32FixedString1024Hash = BasicStringHash<U32FixedString1024>;
using U32FixedString2048Hash = BasicStringHash<U32FixedString2048>;
using U32FixedString4096Hash = BasicStringHash<U32FixedString4096>;
using U32FixedString8192Hash = BasicStringHash<U32FixedString8192>;

} /* namespace tgon */

namespace std
{

template <typename _StringType>
struct hash<tgon::BasicStringHash<_StringType>>
{
/* @section Method */
public:
    auto operator()(const tgon::BasicStringHash<_StringType>& rhs) const noexcept -> decltype(rhs.GetHashCode())
    {
        return rhs.GetHashCode();
    }
};

} /* namespace std */
