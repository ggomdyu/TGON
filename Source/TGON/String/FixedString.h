/**
 * @file    FixedString.h
 * @author  ggomdyu
 * @date    03/16/2017
 * @brief   String class that uses only stack memory and has fixed buffer size.
 */

#pragma once
#include <type_traits>

#include "Core/Range.h"

#include "StringTraits.h"

namespace tgon
{

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType = BasicStringTraits<_CharType>>
class BasicFixedString :
    private _StringTraitsType
{
    static_assert(_CharBufferSize > 0, "The array size of BasicFixedString must be over than 0.");

    static_assert(std::is_same<_CharType, typename _StringTraitsType::ValueType>::value,
        "_StringTraitsType's character type doesn't match with the _CharType.");

/**@section Type */
public:
    using StringTraitsType = _StringTraitsType;
    using SizeType = std::size_t;
    using ValueType = _CharType;
    using ReferenceType = ValueType&;
    using ConstReferenceType = const ValueType&;

/**@section Constructor */
public:
    constexpr BasicFixedString() noexcept;
    BasicFixedString(const _CharType* str);
    BasicFixedString(const std::basic_string_view<_CharType>& str);
    BasicFixedString(std::size_t chCount, _CharType ch);
    template <std::size_t _CharBufferSize2>
    BasicFixedString(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs);

/**@section Operator */
public:
    BasicFixedString& operator=(const std::basic_string_view<_CharType>& rhs);
    BasicFixedString& operator=(const BasicFixedString& rhs) = default;
    template <std::size_t _CharBufferSize2>
    BasicFixedString& operator=(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs);
    const BasicFixedString operator+(const std::basic_string_view<_CharType>& rhs) const;
    template <std::size_t _CharBufferSize2>
    const BasicFixedString operator+(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const;
    const BasicFixedString operator+(_CharType ch) const;
    BasicFixedString& operator+=(const std::basic_string_view<_CharType>& rhs);
    template <std::size_t _CharBufferSize2>
    BasicFixedString& operator+=(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs);
    BasicFixedString& operator+=(_CharType ch);
    bool operator==(const std::basic_string_view<_CharType>& rhs) const;
    template <std::size_t _CharBufferSize2>
    bool operator==(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const;
    const _CharType& operator[](std::size_t index) const;
    _CharType& operator[](std::size_t index);

/**@section Method */
public:
    void Append(const std::basic_string_view<_CharType>& str);
    template <std::size_t _CharBufferSize2>
    void Append(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& str);
    void Append(std::size_t chCount, _CharType ch);
    void Assign(const std::basic_string_view<_CharType>& str);
    template <std::size_t _CharBufferSize2>
    void Assign(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& str);
    void Assign(std::size_t chCount, _CharType ch);
    template <std::size_t _CharBufferSize2>
    BasicFixedString<_CharType, _CharBufferSize + _CharBufferSize2, _StringTraitsType> Expand(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const;
    int32_t Compare(const std::basic_string_view<_CharType>& str) const;
    template <std::size_t _CharBufferSize2>
    int32_t Compare(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& str) const;
    std::size_t Find(const std::basic_string_view<_CharType>& str, std::size_t strOffset) const;
    std::size_t Find(const BasicFixedString& rhs) const;
    template <std::size_t _CharBufferSize2>
    std::size_t Find(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const;
    std::size_t Find(_CharType ch, std::size_t strOffset = 0) const;
    std::size_t RFind(const std::basic_string_view<_CharType>&, std::size_t strOffset) const;
    std::size_t RFind(const BasicFixedString& rhs) const;
    template <std::size_t _CharBufferSize2>
    std::size_t RFind(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const;
    std::size_t RFind(_CharType ch, std::size_t strOffset = _StringTraitsType::NPos) const;
    _CharType& At(std::size_t index);
    const _CharType& At(std::size_t index) const;
    void Swap(BasicFixedString& rhs);
    const _CharType* CStr() const noexcept;
    const _CharType* Data() const noexcept;
    std::size_t Size() const noexcept;
    std::size_t Length() const noexcept;
    constexpr std::size_t Capacity() const noexcept;
    tgon::Range<_CharType> Range() noexcept;
    const tgon::Range<const _CharType> Range() const noexcept;

/**@section Variable */
public:
    using _StringTraitsType::NPos;

protected:
    _CharType m_str[_CharBufferSize];
    std::size_t m_strLen;
};

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType = BasicStringTraits<_CharType>>
constexpr auto MakeFixedString(const _CharType(&str)[_CharBufferSize]) -> BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>
{
    return BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>({str, _CharBufferSize - 1});
}

template <typename>
struct IsBasicFixedString : std::false_type {};

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
struct IsBasicFixedString<BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>> : std::true_type {};

template <typename _Type>
constexpr bool IsBasicFixedString_v = IsBasicFixedString<_Type>::value;;

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

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
constexpr BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::BasicFixedString() noexcept :
    m_str{},
    m_strLen(0)
{
}
    
template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::BasicFixedString(const _CharType* str) :
    BasicFixedString(std::basic_string_view<_CharType>(str))
{
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::BasicFixedString(const std::basic_string_view<_CharType>& str) :
    _StringTraitsType(str, m_str, _CharBufferSize),
    m_strLen(str.length())
{
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::BasicFixedString(std::size_t chCount, _CharType ch) :
    _StringTraitsType(m_str, _CharBufferSize, ch, chCount),
    m_strLen(chCount)
{
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
template <std::size_t _CharBufferSize2>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::BasicFixedString(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) :
    BasicFixedString({rhs.CStr(), rhs.Length()})
{
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
template <std::size_t _CharBufferSize2>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator=(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs)
{
    this->Assign(rhs);
    return *this;
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator=(const std::basic_string_view<_CharType>& rhs)
{
    this->Assign(rhs);
    return *this;
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
template <std::size_t _CharBufferSize2>
inline const BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType> BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator+(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const
{
    return (BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>(*this) += rhs);
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline const BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType> BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator+(const std::basic_string_view<_CharType>& rhs) const
{
    return (BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>(*this) += rhs);
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline const BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType> BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator+(_CharType ch) const
{
    return (BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>(*this) += ch);
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
template <std::size_t _CharBufferSize2>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator+=(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs)
{
    this->Append({rhs.CStr(), rhs.Length()});
    return *this;
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator+=(const std::basic_string_view<_CharType>& rhs)
{
    this->Append(rhs);
    return *this;
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator+=(_CharType ch)
{
    this->Append(1, ch);
    return *this;
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline bool BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator==(const std::basic_string_view<_CharType>& rhs) const
{
    return _StringTraitsType::Compare({m_str, m_strLen}, rhs) == 0;
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
template <std::size_t _CharBufferSize2>
inline bool BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator==(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const
{
    return _StringTraitsType::Compare({m_str, m_strLen}, rhs.CStr(), rhs.Length()) == 0;
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline const _CharType& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator[](std::size_t index) const
{
    return _StringTraitsType::At(m_str, index);
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline _CharType& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::operator[](std::size_t index)
{
    return _StringTraitsType::At(m_str, index);
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
template <std::size_t _CharBufferSize2>
inline BasicFixedString<_CharType, _CharBufferSize + _CharBufferSize2, _StringTraitsType> BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Expand(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const
{
    return BasicFixedString<_CharType, _CharBufferSize + _CharBufferSize2, _StringTraitsType>(*this) += rhs;
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline void BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Append(const std::basic_string_view<_CharType>& str)
{
    _StringTraitsType::Append(str, m_str, m_strLen, _CharBufferSize);
    m_strLen += str.length();
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
template <std::size_t _CharBufferSize2>
inline void BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Append(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& str)
{
    this->Append({str.CStr(), str.Length()});
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline void BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Append(std::size_t chCount, _CharType ch)
{
    _StringTraitsType::Append({m_str, m_strLen}, _CharBufferSize, ch, chCount);
    m_strLen += chCount;
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
template <std::size_t _CharBufferSize2>
inline void BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Assign(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& str)
{
    new (this) BasicFixedString(str);
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline void BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Assign(const std::basic_string_view<_CharType>& str)
{
    new (this) BasicFixedString(str);
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline void BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Assign(std::size_t chCount, _CharType ch)
{
    new (this) BasicFixedString(chCount, ch);
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
template <std::size_t _CharBufferSize2>
inline int32_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Compare(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& str) const
{
    return _StringTraitsType::Compare(m_str, m_strLen, str.CStr(), str.Length());
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline int32_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Compare(const std::basic_string_view<_CharType>& str) const
{
    return _StringTraitsType::Compare({m_str, m_strLen}, str);
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
template <std::size_t _CharBufferSize2>
inline std::size_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Find(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const
{
    return _StringTraitsType::Find(m_str, m_strLen, 0, rhs.CStr(), rhs.Length());
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline std::size_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Find(const BasicFixedString& rhs) const
{
    return _StringTraitsType::Find(m_str, m_strLen, 0, rhs.CStr(), rhs.Length());
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline std::size_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Find(_CharType ch, std::size_t strOffset) const
{
    return _StringTraitsType::Find({m_str, m_strLen}, strOffset, &ch, 1);
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline std::size_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Find(const std::basic_string_view<_CharType>& str, std::size_t strOffset) const
{
    return _StringTraitsType::Find({m_str, m_strLen}, strOffset, str, str.length());
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
template <std::size_t _CharBufferSize2>
inline std::size_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::RFind(const BasicFixedString<_CharType, _CharBufferSize2, _StringTraitsType>& rhs) const
{
    return _StringTraitsType::RFind({m_str, m_strLen}, 0, rhs.CStr(), rhs.Length());
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline std::size_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::RFind(const BasicFixedString& rhs) const
{
    return _StringTraitsType::RFind({m_str, m_strLen}, 0, rhs.CStr(), rhs.Length());
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline std::size_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::RFind(_CharType ch, std::size_t strOffset) const
{
    return _StringTraitsType::RFind({m_str, m_strLen}, strOffset, &ch, 1);
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline std::size_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::RFind(const std::basic_string_view<_CharType>& str, std::size_t strOffset) const
{
    return _StringTraitsType::RFind({m_str, m_strLen}, strOffset, str, str.length());
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline void BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Swap(BasicFixedString& rhs)
{
    _StringTraitsType::Swap(&m_str[0], m_strLen, _CharBufferSize, &rhs[0], rhs.Length(), rhs.Capacity());
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline const _CharType* BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::CStr() const noexcept
{
    return m_str;
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline const _CharType* BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Data() const noexcept
{
    return m_str;
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline std::size_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Size() const noexcept
{
    return m_strLen;
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline std::size_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Length() const noexcept
{
    return this->Size();
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
constexpr std::size_t BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Capacity() const noexcept
{
    return _CharBufferSize;
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline _CharType& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::At(std::size_t index)
{
    return _StringTraitsType::At(m_str, index);
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline const _CharType& BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::At(std::size_t index) const
{
    return _StringTraitsType::At(m_str, index);
}
 
template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline const Range<const _CharType> BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Range() const noexcept
{
    return {m_str, m_str + m_strLen};
}

template <typename _CharType, std::size_t _CharBufferSize, typename _StringTraitsType>
inline Range<_CharType> BasicFixedString<_CharType, _CharBufferSize, _StringTraitsType>::Range() noexcept
{
    return { m_str, m_str + m_strLen };
}

} /* namespace tgon */
