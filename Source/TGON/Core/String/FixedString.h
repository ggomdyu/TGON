/**
 * @filename    FixedString.h
 * @author      ggomdyu
 * @date        03/16/2017
 * @brief       String class that uses only stack memory and has fixed buffer size.
 */

#pragma once
#include <cstdint>

#include "StringTraits.h"

namespace tgon
{
namespace string
{

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType = StringTraits<_CharType>>
class BasicFixedString :
    private _StringTraitsType
{
    static_assert(_CharArraySize > 0, "The array size of BasicFixedString must be over than 0.");

/* @section Public type */
public:
    using CharType = _CharType;
    using ReferenceType = CharType&;
    using ConstReferenceType = const CharType&;
    using IteratorType = CharType*;
    using ConstIteratorType = const CharType*;
    using PointerType = CharType*;
    using ConstPointerType = const CharType*;
    using ReverseIteratorType = std::reverse_iterator<IteratorType>;
    using ConstReverseIteratorType = std::reverse_iterator<ConstIteratorType>;

/* @section Public constructor */
public:
    constexpr BasicFixedString() noexcept;
    template <std::size_t _CharArraySize2>
    BasicFixedString(const _CharType(&str)[_CharArraySize2]);
    template <typename _CharPointerType, typename std::enable_if_t<std::is_pointer<_CharPointerType>::value>* = nullptr>
    BasicFixedString(const _CharPointerType str);
    BasicFixedString(const _CharType* str, std::size_t strLen);
    BasicFixedString(std::size_t chCount, _CharType ch);

    template <std::size_t _CharArraySize2>
    BasicFixedString(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs);

/* @section Public operator */
public:
    template <std::size_t _CharArraySize2>
    BasicFixedString& operator=(const _CharType(&rhs)[_CharArraySize2]);
    template <typename _CharPointerType, typename std::enable_if_t<std::is_pointer<_CharPointerType>::value>* = nullptr>
    BasicFixedString& operator=(const _CharPointerType rhs);
    BasicFixedString& operator=(const BasicFixedString& rhs) = default;
    template <std::size_t _CharArraySize2>
    BasicFixedString& operator=(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs);

    template <std::size_t _CharArraySize2>
    const BasicFixedString operator+(const _CharType(&rhs)[_CharArraySize2]);
    template <typename _CharPointerType, typename std::enable_if_t<std::is_pointer<_CharPointerType>::value>* = nullptr>
    const BasicFixedString operator+(const _CharPointerType rhs) const;
    template <std::size_t _CharArraySize2>
    const BasicFixedString operator+(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs) const;
    const BasicFixedString operator+(_CharType ch) const;

    template <std::size_t _CharArraySize2>
    BasicFixedString& operator+=(const _CharType(&rhs)[_CharArraySize2]);
    template <typename _CharPointerType, typename std::enable_if_t<std::is_pointer<_CharPointerType>::value>* = nullptr>
    BasicFixedString& operator+=(const _CharPointerType rhs);
    template <std::size_t _CharArraySize2>
    BasicFixedString& operator+=(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs);
    BasicFixedString& operator+=(_CharType ch);

    template <std::size_t _CharArraySize2>
    bool operator==(const _CharType(&rhs)[_CharArraySize2]) const;
    template<typename _CharPointerType, std::enable_if_t<std::is_pointer<_CharPointerType>::value>* = nullptr>
    bool operator==(const _CharPointerType rhs) const;
    template <std::size_t _CharArraySize2>
    bool operator==(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs) const;

    const _CharType& operator[](std::size_t index) const;
    _CharType& operator[](std::size_t index);

/* @section Public method */
public:
    void Append(const _CharType* str, std::size_t strLen);
    template <std::size_t _CharArraySize2>
    void Append(const _CharType(&str)[_CharArraySize2]);
    template<typename _CharPointerType, std::enable_if_t<std::is_pointer<_CharPointerType>::value>* = nullptr>
    void Append(const _CharPointerType str);
    template <std::size_t _CharArraySize2>
    void Append(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& str);
    void Append(std::size_t chCount, _CharType ch);

    void Assign(const _CharType* str, std::size_t strLen);
    template <std::size_t _CharArraySize2>
    void Assign(const _CharType(&str)[_CharArraySize2]);
    template<typename _CharPointerType, std::enable_if_t<std::is_pointer<_CharPointerType>::value>* = nullptr>
    void Assign(const _CharPointerType str);
    template <std::size_t _CharArraySize2>
    void Assign(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& str);
    void Assign(std::size_t chCount, _CharType ch);

    template <std::size_t _CharArraySize2>
    BasicFixedString<_CharType, _CharArraySize + _CharArraySize2, _StringTraitsType> Expand(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs) const;
    template <std::size_t _CharArraySize2>
    BasicFixedString<_CharType, _CharArraySize + _CharArraySize2, _StringTraitsType> Expand(const _CharType(&rhs)[_CharArraySize2]) const;

    int32_t Compare(const _CharType* str, std::size_t strLen) const;
    template <std::size_t _CharArraySize2>
    int32_t Compare(const _CharType(&str)[_CharArraySize2]) const;
    template<typename _CharPointerType, std::enable_if_t<std::is_pointer<_CharPointerType>::value>* = nullptr>
    int32_t Compare(const _CharPointerType str) const;
    template <std::size_t _CharArraySize2>
    int32_t Compare(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& str) const;

    template <std::size_t _CharArraySize2>
    std::size_t Find(const _CharType(&str)[_CharArraySize2], std::size_t strOffset = 0) const;
    std::size_t Find(const _CharType* str, std::size_t strOffset, std::size_t strLen) const;
    std::size_t Find(const BasicFixedString& rhs) const;
    template <std::size_t _CharArraySize2>
    std::size_t Find(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs) const;
    std::size_t Find(_CharType ch, std::size_t strOffset = 0) const;

    std::size_t RFind(const _CharType* str, std::size_t strOffset, std::size_t strLen) const;
    template <std::size_t _CharArraySize2>
    std::size_t RFind(const _CharType(&str)[_CharArraySize2], std::size_t strOffset = _StringTraitsType::NPos) const;
    std::size_t RFind(const BasicFixedString& rhs) const;
    template <std::size_t _CharArraySize2>
    std::size_t RFind(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs) const;
    std::size_t RFind(_CharType ch, std::size_t strOffset = _StringTraitsType::NPos) const;

    _CharType& At(std::size_t index);
    const _CharType& At(std::size_t index) const;

    void Swap(BasicFixedString& rhs);

    const _CharType* CStr() const noexcept;
    const _CharType* Data() const noexcept;

    std::size_t Length() const noexcept;
    constexpr std::size_t Capacity() const noexcept;

    IteratorType begin() noexcept;
    IteratorType end() noexcept;
    ConstIteratorType cbegin() const noexcept;
    ConstIteratorType cend() const noexcept;
    ReverseIteratorType rbegin() noexcept;
    ReverseIteratorType rend() noexcept;
    ConstReverseIteratorType crbegin() const noexcept;
    ConstReverseIteratorType crend() const noexcept;

/* @section Public variable */
public:
    using _StringTraitsType::NPos;

/* @section Private variable */
private:
    _CharType m_str[_CharArraySize];
    std::size_t m_strLen;
};

using FixedString8 = BasicFixedString<char, 8>;
using FixedString16 = BasicFixedString<char, 16>;
using FixedString32 = BasicFixedString<char, 32>;
using FixedString64 = BasicFixedString<char, 64>;
using FixedString128 = BasicFixedString<char, 128>;

using FixedWString8 = BasicFixedString<wchar_t, 8>;
using FixedWString16 = BasicFixedString<wchar_t, 16>;
using FixedWString32 = BasicFixedString<wchar_t, 32>;
using FixedWString64 = BasicFixedString<wchar_t, 64>;
using FixedWString128 = BasicFixedString<wchar_t, 128>;

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
constexpr BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::BasicFixedString() noexcept :
    m_str{},
    m_strLen(0)
{
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::BasicFixedString(const _CharType(&str)[_CharArraySize2]) :
    BasicFixedString(str, _CharArraySize2 - 1)
{
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <typename _CharPointerType, typename std::enable_if_t<std::is_pointer<_CharPointerType>::value>*>
inline BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::BasicFixedString(const _CharPointerType str) :
    BasicFixedString(str, _StringTraitsType::Length(str))
{
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::BasicFixedString(const _CharType* str, std::size_t strLen) :
    _StringTraitsType(str, strLen, m_str, _CharArraySize),
    m_strLen(strLen)
{
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::BasicFixedString(std::size_t chCount, _CharType ch) :
    _StringTraitsType(m_str, _CharArraySize, ch, chCount),
    m_strLen(chCount)
{
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::BasicFixedString(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs) :
    BasicFixedString(rhs.CStr(), rhs.Length())
{
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>& BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator=(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs)
{
    this->Assign(rhs);
    return *this;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>& BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator=(const _CharType(&rhs)[_CharArraySize2])
{
    this->Assign(rhs);
    return *this;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <typename _CharPointerType, typename std::enable_if_t<std::is_pointer<_CharPointerType>::value>*>
inline BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>& BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator=(const _CharPointerType rhs)
{
    this->Assign(rhs);
    return *this;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline const BasicFixedString<_CharType, _CharArraySize, _StringTraitsType> BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator+(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs) const
{
    return (BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>(*this) += rhs);
}

template<typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template<std::size_t _CharArraySize2>
inline const BasicFixedString<_CharType, _CharArraySize, _StringTraitsType> BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator+(const _CharType(&rhs)[_CharArraySize2])
{
    return (BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>(*this) += rhs);
}

template<typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template<typename _CharPointerType, typename std::enable_if_t<std::is_pointer<_CharPointerType>::value>*>
inline const BasicFixedString<_CharType, _CharArraySize, _StringTraitsType> BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator+(const _CharPointerType rhs) const
{
    return (BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>(*this) += rhs);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline const BasicFixedString<_CharType, _CharArraySize, _StringTraitsType> BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator+(_CharType ch) const
{
    return (BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>(*this) += ch);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>& BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator+=(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs)
{
    this->Append(rhs.CStr(), rhs.Length());
    return *this;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>& BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator+=(const _CharType(&rhs)[_CharArraySize2])
{
    this->Append(rhs, _CharArraySize2 - 1);
    return *this;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <typename _CharPointerType, typename std::enable_if_t<std::is_pointer<_CharPointerType>::value>*>
inline BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>& BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator+=(const _CharPointerType rhs)
{
    this->Append(rhs);
    return *this;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>& BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator+=(_CharType ch)
{
    this->Append(1, ch);
    return *this;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <typename _CharPointerType, std::enable_if_t<std::is_pointer<_CharPointerType>::value>*>
inline bool BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator==(const _CharPointerType rhs) const
{
    return _StringTraitsType::Compare(m_str, m_strLen, rhs, _StringTraitsType::Length(rhs)) == 0;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline bool BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator==(const _CharType(&rhs)[_CharArraySize2]) const
{
    return _StringTraitsType::Compare(m_str, m_strLen, rhs, _CharArraySize2 - 1) == 0;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline bool BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator==(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs) const
{
    return _StringTraitsType::Compare(m_str, m_strLen, rhs.CStr(), rhs.Length()) == 0;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline const _CharType& BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator[](std::size_t index) const
{
	return _StringTraitsType::At(m_str, m_strLen, index);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline _CharType& BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::operator[](std::size_t index)
{
	return _StringTraitsType::At(m_str, m_strLen, index);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize + _CharArraySize2, _StringTraitsType> BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Expand(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs) const
{
	return BasicFixedString<_CharType, _CharArraySize + _CharArraySize2, _StringTraitsType>(*this) += rhs;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize + _CharArraySize2, _StringTraitsType> BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Expand(const _CharType(&rhs)[_CharArraySize2]) const
{
    return BasicFixedString<_CharType, _CharArraySize + _CharArraySize2, _StringTraitsType>(*this) += rhs;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline void BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Append(const _CharType* str, std::size_t strLen)
{
    _StringTraitsType::Append(str, strLen, m_str, m_strLen, _CharArraySize);
    m_strLen += strLen;
}

template<typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template<std::size_t _CharArraySize2>
inline void BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Append(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& str)
{
    this->Append(str.CStr(), str.Length());
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline void BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Append(const _CharType(&str)[_CharArraySize2])
{
    this->Append(str, _CharArraySize2 - 1);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <typename _CharPointerType, std::enable_if_t<std::is_pointer<_CharPointerType>::value>*>
inline void BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Append(const _CharPointerType str)
{
    this->Append(str, _StringTraitsType::Length(str));
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline void BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Append(std::size_t chCount, _CharType ch)
{
    _StringTraitsType::Append(m_str, m_strLen, _CharArraySize, ch, chCount);
    m_strLen += chCount;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline void BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Assign(const _CharType(&str)[_CharArraySize2])
{
    new (this) BasicFixedString(str, _CharArraySize2 - 1);
}

template<typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template<typename _CharPointerType, std::enable_if_t<std::is_pointer<_CharPointerType>::value>*>
inline void BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Assign(const _CharPointerType str)
{
    new (this) BasicFixedString(str);
}

template<typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template<std::size_t _CharArraySize2>
inline void BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Assign(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& str)
{
    new (this) BasicFixedString(str);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline void BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Assign(const _CharType* str, std::size_t strLen)
{
    new (this) BasicFixedString(str, strLen);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline void BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Assign(std::size_t chCount, _CharType ch)
{
    new (this) BasicFixedString(chCount, ch);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline int32_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Compare(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& str) const
{
    return _StringTraitsType::Compare(m_str, m_strLen, str.CStr(), str.Length());
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline int32_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Compare(const _CharType(&str)[_CharArraySize2]) const
{
    return _StringTraitsType::Compare(m_str, m_strLen, str, _CharArraySize2 - 1);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline int32_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Compare(const _CharType* str, std::size_t strLen) const
{
    return _StringTraitsType::Compare(m_str, m_strLen, str, strLen);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <typename _CharPointerType, std::enable_if_t<std::is_pointer<_CharPointerType>::value>*>
inline int32_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Compare(const _CharPointerType str) const
{
    return _StringTraitsType::Compare(m_str, m_strLen, str, _StringTraitsType::Length(str));
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Find(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs) const
{
    return _StringTraitsType::Find(m_str, m_strLen, 0, rhs.CStr(), rhs.Length());
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Find(const BasicFixedString& rhs) const
{
    return _StringTraitsType::Find(m_str, m_strLen, 0, rhs.CStr(), rhs.Length());
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Find(_CharType ch, std::size_t strOffset) const
{
	return _StringTraitsType::Find(m_str, m_strLen, strOffset, &ch, 1);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Find(const _CharType(&str)[_CharArraySize2], std::size_t strOffset) const
{
    return _StringTraitsType::Find(m_str, m_strLen, strOffset, str, _CharArraySize2 - 1);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Find(const _CharType* str, std::size_t strOffset, std::size_t strLen) const
{
    return _StringTraitsType::Find(m_str, m_strLen, strOffset, str, strLen);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::RFind(const BasicFixedString<_CharType, _CharArraySize2, _StringTraitsType>& rhs) const
{
    return _StringTraitsType::RFind(m_str, m_strLen, 0, rhs.CStr(), rhs.Length());
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::RFind(const BasicFixedString& rhs) const
{
    return _StringTraitsType::RFind(m_str, m_strLen, 0, rhs.CStr(), rhs.Length());
}

template<typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::RFind(_CharType ch, std::size_t strOffset) const
{
    return _StringTraitsType::RFind(m_str, m_strLen, strOffset, &ch, 1);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::RFind(const _CharType(&str)[_CharArraySize2], std::size_t strOffset) const
{
    return _StringTraitsType::RFind(m_str, m_strLen, strOffset, str, _CharArraySize2 - 1);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::RFind(const _CharType* str, std::size_t strOffset, std::size_t strLen) const
{
    return _StringTraitsType::RFind(m_str, m_strLen, strOffset, str, strLen);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline void BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Swap(BasicFixedString& rhs)
{
    _StringTraitsType::Swap(&m_str[0], m_strLen, _CharArraySize, &rhs[0], rhs.Length(), rhs.Capacity());
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline const _CharType* BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::CStr() const noexcept
{
    return m_str;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline const _CharType* BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Data() const noexcept
{
    return m_str;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Length() const noexcept
{
    return m_strLen;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
constexpr std::size_t BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::Capacity() const noexcept
{
    return _CharArraySize;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline typename BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::IteratorType BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::begin() noexcept
{
    return m_str;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline typename BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::IteratorType BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::end() noexcept
{
    return m_str + m_strLen;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline typename BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::ConstIteratorType BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::cbegin() const noexcept
{
    return m_str;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline typename BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::ConstIteratorType BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::cend() const noexcept
{
    return m_str + m_strLen;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline typename BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::ReverseIteratorType BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::rbegin() noexcept
{
    return ConstReverseIteratorType(m_str + m_strLen);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline typename BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::ReverseIteratorType BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::rend() noexcept
{
    return ConstReverseIteratorType(m_str);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline typename BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::ConstReverseIteratorType BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::crbegin() const noexcept
{
    return ConstReverseIteratorType(m_str + m_strLen);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline typename BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::ConstReverseIteratorType BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::crend() const noexcept
{
    return ConstReverseIteratorType(m_str);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline _CharType& BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::At(std::size_t index)
{
    return _StringTraitsType::At(m_str, m_strLen, index);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline const _CharType BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>::At(std::size_t index) const
{
    return _StringTraitsType::At(m_str, m_strLen, index);
}

} /* namespace string */
} /* namespace tgon */
