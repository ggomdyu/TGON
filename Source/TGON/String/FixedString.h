/**
 * @file    FixedString.h
 * @author  ggomdyu
 * @date    03/16/2017
 * @brief   String class that uses only stack memory and has fixed buffer size.
 */

#pragma once
#include <type_traits>

#include "StringTraits.h"

namespace tgon
{

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType = BasicStringTraits<_CharType>>
class BasicFixedString final
{
    static_assert(std::is_same<_CharType, typename _StringTraitsType::ValueType>::value,
        "_StringTraitsType's character type doesn't match with the _CharType.");

/**@section Type */
public:
    using StringTraitsType = _StringTraitsType;
    using ValueType = _CharType;
    using IteratorType = _CharType *;
    using ConstIteratorType = const _CharType*;
    using ReferenceType = _CharType&;
    using ConstReferenceType = const _CharType&;

/**@section Constructor */
public:
    constexpr BasicFixedString() noexcept;
    BasicFixedString(const _CharType* str);
    BasicFixedString(const std::basic_string_view<_CharType>& str);
    BasicFixedString(_CharType ch, int32_t chCount);
    template <int32_t _CharBufferSize2>
    BasicFixedString(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& str);

/**@section Operator */
public:
    BasicFixedString& operator=(const std::basic_string_view<_CharType>& rhs);
    template <int32_t _CharBufferSize2>
    BasicFixedString& operator=(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs);
    const BasicFixedString operator+(const std::basic_string_view<_CharType>& rhs) const;
    template <int32_t _CharBufferSize2>
    const BasicFixedString operator+(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const;
    const BasicFixedString operator+(_CharType rhs) const;
    BasicFixedString& operator+=(const std::basic_string_view<_CharType>& rhs);
    template <int32_t _CharBufferSize2>
    BasicFixedString& operator+=(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs);
    BasicFixedString& operator+=(_CharType ch);
    bool operator!=(const std::basic_string_view<_CharType>& rhs) const;
    template <int32_t _CharBufferSize2>
    bool operator!=(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const;
    bool operator==(const std::basic_string_view<_CharType>& rhs) const;
    template <int32_t _CharBufferSize2>
    bool operator==(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const;
    const _CharType& operator[](int32_t index) const;
    _CharType& operator[](int32_t index);
    operator std::basic_string<_CharType>() const noexcept;
    operator std::basic_string_view<_CharType>() const noexcept;

/**@section Method */
public:
    template <int32_t _CharBufferSize2>
    BasicFixedString<_CharType, _CharBufferSize + _CharBufferSize2, _StringTraitsType> Expand(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const;
    template <int32_t _CharBufferSize2>
    int32_t CompareTo(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& str) const;
    int32_t CompareTo(const std::basic_string_view<_CharType>& str) const;
    int32_t IndexOf(const std::basic_string_view<_CharType>& str, int32_t startIndex = 0) const;
    int32_t IndexOf(_CharType ch, int32_t startIndex = 0) const;
    template<typename _PredicateType>
    int32_t IndexOfAny(const _PredicateType& predicate, int32_t startIndex = 0) const;
    int32_t LastIndexOf(const std::basic_string_view<_CharType>& str) const;
    int32_t LastIndexOf(const std::basic_string_view<_CharType>& str, int32_t startIndex = 0) const;
    int32_t LastIndexOf(_CharType ch) const;
    int32_t LastIndexOf(_CharType ch, int32_t startIndex) const;
    template<typename _PredicateType>
    int32_t LastIndexOfAny(const _PredicateType& predicate) const;
    template<typename _PredicateType>
    int32_t LastIndexOfAny(const _PredicateType& predicate, int32_t startIndex) const;
    const _CharType* Data() const noexcept;
    int32_t Length() const noexcept;
    constexpr int32_t Capacity() const noexcept;
    IteratorType Begin() noexcept;
    IteratorType End() noexcept;
    ConstIteratorType CBegin() const noexcept;
    ConstIteratorType CEnd() const noexcept;

/**@section Variable */
protected:
    _CharType m_str[_CharBufferSize];
    int32_t m_strLen;
};

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType = BasicStringTraits<_CharType>>
BasicFixedString(const _CharType(&)[_CharBufferSize]) -> BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>;

template <typename>
struct IsBasicFixedString : std::false_type {};

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
struct IsBasicFixedString<BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>> : std::true_type {};

template <typename _Type>
constexpr bool IsBasicFixedStringValue = IsBasicFixedString<_Type>::value;;

using FixedString8 = BasicFixedString<char, 8>;
using FixedString16 = BasicFixedString<char, 16>;
using FixedString32 = BasicFixedString<char, 32>;
using FixedString64 = BasicFixedString<char, 64>;
using FixedString128 = BasicFixedString<char, 128>;
using FixedString256 = BasicFixedString<char, 256>;
using FixedString512 = BasicFixedString<char, 512>;
using FixedString1024 = BasicFixedString<char, 1024>;

using FixedWString8 = BasicFixedString<wchar_t, 8>;
using FixedWString16 = BasicFixedString<wchar_t, 16>;
using FixedWString32 = BasicFixedString<wchar_t, 32>;
using FixedWString64 = BasicFixedString<wchar_t, 64>;
using FixedWString128 = BasicFixedString<wchar_t, 128>;
using FixedWString256 = BasicFixedString<wchar_t, 256>;
using FixedWString512 = BasicFixedString<wchar_t, 512>;
using FixedWString1024 = BasicFixedString<wchar_t, 1024>;

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
constexpr BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::BasicFixedString() noexcept :
    m_str{},
    m_strLen(0)
{
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::BasicFixedString(const _CharType* str) :
    BasicFixedString(std::basic_string_view<_CharType>(str))
{
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::BasicFixedString(const std::basic_string_view<_CharType>& str) :
    BasicFixedString()
{
    _StringTraitsType::Append(str.data(), static_cast<int32_t>(str.length()), m_str, m_strLen);
    m_strLen += str.length();
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::BasicFixedString(_CharType ch, int32_t chCount) :
    BasicFixedString()
{
    _StringTraitsType::Append(m_str, m_strLen, ch, chCount);
    m_strLen += chCount;
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
template <int32_t _CharBufferSize2>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::BasicFixedString(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) :
    BasicFixedString({rhs.Data(), rhs.Length()})
{
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
template <int32_t _CharBufferSize2>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator=(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs)
{
    this->Assign(rhs);
    return *this;
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator=(const std::basic_string_view<_CharType>& rhs)
{
    this->Assign(rhs);
    return *this;
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
template <int32_t _CharBufferSize2>
inline const BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType> BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator+(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const
{
    return (BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>(*this) += rhs);
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline const BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType> BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator+(const std::basic_string_view<_CharType>& rhs) const
{
    return (BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>(*this) += rhs);
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline const BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType> BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator+(_CharType ch) const
{
    return (BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>(*this) += ch);
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
template <int32_t _CharBufferSize2>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator+=(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs)
{
    return this->operator+=({rhs.Data(), rhs.Length()});
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator+=(const std::basic_string_view<_CharType>& rhs)
{
    _StringTraitsType::Append(rhs.data(), static_cast<int32_t>(rhs.length()), m_str, m_strLen);
    m_strLen += rhs.length();

    return *this;
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator+=(_CharType rhs)
{
    _StringTraitsType::Append(m_str, m_strLen, rhs, 1);
    m_strLen += 1;

    return *this;
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline bool BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator!=(const std::basic_string_view<_CharType>& rhs) const
{
    return !this->operator==(rhs);
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
template <int32_t _CharBufferSize2>
inline bool BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator!=(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const
{
    return !this->operator==(rhs);
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
template <int32_t _CharBufferSize2>
inline bool BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator==(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const
{
    return _StringTraitsType::Compare(m_str, m_strLen, rhs.Data(), rhs.Length()) == 0;
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline bool BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator==(const std::basic_string_view<_CharType>& rhs) const
{
    return _StringTraitsType::Compare(m_str, m_strLen, rhs.data(), rhs.length()) == 0;
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline const _CharType& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator[](int32_t index) const
{
    return m_str[index];
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline _CharType& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator[](int32_t index)
{
    return m_str[index];
}

template<typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator std::basic_string_view<_CharType>() const noexcept
{
    return {m_str, m_strLen};
}

template<typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator std::basic_string<_CharType>() const noexcept
{
    return {m_str, m_strLen};
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
template <int32_t _CharBufferSize2>
inline BasicFixedString<_CharType, _CharBufferSize + _CharBufferSize2, _StringTraitsType> BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Expand(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const
{
    return BasicFixedString<_CharType, _CharBufferSize + _CharBufferSize2, _StringTraitsType>(*this) += rhs;
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
template <int32_t _CharBufferSize2>
inline int32_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::CompareTo(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& str) const
{
    return _StringTraitsType::Compare(m_str, static_cast<size_t>(m_strLen), str.Data(), static_cast<size_t>(str.Length()));
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline int32_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::CompareTo(const std::basic_string_view<_CharType>& str) const
{
    return _StringTraitsType::Compare(m_str, m_strLen, str.length(), str.data());
}

template<typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
template<typename _PredicateType>
inline int32_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::IndexOfAny(const _PredicateType& predicate, int32_t startIndex) const
{
    return _StringTraitsType::IndexOfAny(m_str + startIndex, m_strLen - startIndex, predicate) + startIndex;
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline int32_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::IndexOf(_CharType ch, int32_t startIndex) const
{
    char str[] = {ch, '\0'};
    return _StringTraitsType::IndexOf(m_str + startIndex, m_strLen - startIndex, str, 1) + startIndex;
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline int32_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::IndexOf(const std::basic_string_view<_CharType>& str, int32_t startIndex) const
{
    return _StringTraitsType::IndexOf(m_str + startIndex, m_strLen - startIndex, str, str.length()) + startIndex;
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline int32_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::LastIndexOf(_CharType ch, int32_t startIndex) const
{
    char str[] = {ch, '\0'};
    return _StringTraitsType::LastIndexOf(m_str, startIndex + 1, str, 1);
}

template<typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline int32_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::LastIndexOf(const std::basic_string_view<_CharType>& str) const
{
    return _StringTraitsType::LastIndexOf(m_str, m_strLen, str, str.length());
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline int32_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::LastIndexOf(const std::basic_string_view<_CharType>& str, int32_t startIndex) const
{
    return _StringTraitsType::LastIndexOf(m_str, startIndex, str, str.length());
}

template<typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline int32_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::LastIndexOf(_CharType ch) const
{
    return _StringTraitsType::LastIndexOf(m_str, m_strLen, &ch, 1);
}

template<typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
template<typename _PredicateType>
inline int32_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::LastIndexOfAny(const _PredicateType& predicate) const
{
    return _StringTraitsType::LastIndexOfAny(m_str, m_strLen, predicate);
}

template<typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
template<typename _PredicateType>
inline int32_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::LastIndexOfAny(const _PredicateType& predicate, int32_t startIndex) const
{
    return _StringTraitsType::LastIndexOfAny(m_str, startIndex, predicate);
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline const _CharType* BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Data() const noexcept
{
    return m_str;
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline int32_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Length() const noexcept
{
    return m_strLen;
}

template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
constexpr int32_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Capacity() const noexcept
{
    return _CharBufferSize;
}

template<typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline typename BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::IteratorType BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Begin() noexcept
{
    return m_str;
}
 
template <typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline typename BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::IteratorType BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::End() noexcept
{
    return m_strLen;
}

template<typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline typename BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::ConstIteratorType BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::CBegin() const noexcept
{
    return this->Begin();
}

template<typename _CharType, int32_t _CharBufferSize, typename _StringTraitsType>
inline typename BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::ConstIteratorType BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::CEnd() const noexcept
{
    return this->End();
}

} /* namespace tgon */

//Swap
//_StringTraitsType::Swap(&m_str[0], m_strLen, _CharBufferSize, &rhs[0], rhs.Length(), rhs.Capacity());
