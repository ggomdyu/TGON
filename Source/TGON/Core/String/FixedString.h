/**
 * @filename    FixedString.h
 * @author      ggomdyu
 * @date        03/16/2017
 */

#pragma once
#include <memory>
#include <cstdint>
#include <cassert>

#include "StringTraits.h"

namespace tgon
{
namespace string
{

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
class BasicFixedString :
    private StringTraits
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
    BasicFixedString(const _CharType* str, std::size_t strLen);
    BasicFixedString(std::size_t chCount, _CharType ch);

    template <std::size_t _CharArraySize2>
    BasicFixedString(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs);

/* @section Public operator */
public:
    template <std::size_t _CharArraySize2>
    BasicFixedString& operator=(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs);
    BasicFixedString& operator=(const BasicFixedString& rhs) = default;

    template <std::size_t _CharArraySize2>
    BasicFixedString operator+(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs) const;
    template <std::size_t _CharArraySize2>
    BasicFixedString operator+(const _CharType(&rhs)[_CharArraySize2]);
    BasicFixedString operator+(_CharType ch) const;

    template <std::size_t _CharArraySize2>
    BasicFixedString& operator+=(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs);
    template <std::size_t _CharArraySize2>
    BasicFixedString& operator+=(const _CharType(&rhs)[_CharArraySize2]);
    BasicFixedString& operator+=(_CharType ch);

    template <std::size_t _CharArraySize2>
    bool operator==(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs) const;

    _CharType operator[](std::size_t index) const;
    _CharType& operator[](std::size_t index);

/* @section Public method */
public:
    template <std::size_t _CharArraySize2>
    BasicFixedString<_CharType, _CharArraySize + _CharArraySize2, StringTraits> Expand(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs) const;

    template <std::size_t _CharArraySize2>
    void Append(const _CharType(&str)[_CharArraySize2]);
    void Append(const _CharType* str, std::size_t strLen);
    void Append(std::size_t chCount, _CharType ch);

    template <std::size_t _CharArraySize2>
    void Assign(const _CharType(&str)[_CharArraySize2]);
    void Assign(const _CharType* str, std::size_t strLen);
    void Assign(std::size_t chCount, _CharType ch);

    template <std::size_t _CharArraySize2>
    int32_t Compare(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs) const;

    template <std::size_t _CharArraySize2>
    std::size_t Find(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs) const;
    std::size_t Find(const BasicFixedString& rhs) const;
    std::size_t Find(_CharType ch, std::size_t strOffset = 0) const;
    template <std::size_t _CharArraySize2>
    std::size_t Find(const _CharType(&str)[_CharArraySize2], std::size_t strOffset = 0) const;
    std::size_t Find(const _CharType* str, std::size_t strOffset, std::size_t strLen) const;

    template <std::size_t _CharArraySize2>
    std::size_t RFind(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs) const;
    std::size_t RFind(const BasicFixedString& rhs) const;
    std::size_t RFind(_CharType ch, std::size_t strOffset = StringTraits::NPos) const;
    template <std::size_t _CharArraySize2>
    std::size_t RFind(const _CharType(&str)[_CharArraySize2], std::size_t strOffset = StringTraits::NPos) const;
    std::size_t RFind(const _CharType* str, std::size_t strOffset, std::size_t strLen) const;

    _CharType& At(std::size_t index);
    const _CharType At(std::size_t index) const;

    void Swap(BasicFixedString& rhs);

    const _CharType* CStr() const noexcept;

    std::size_t Length() const noexcept;
    constexpr std::size_t Capacity() const noexcept;

    IteratorType begin() noexcept;
    IteratorType end();
    ConstIteratorType cbegin() const noexcept;
    ConstIteratorType cend() const;
    ReverseIteratorType rbegin();
    ReverseIteratorType rend() noexcept;
    ConstReverseIteratorType rbegin() const;
    ConstReverseIteratorType rend() const noexcept;

/* @section Private variable */
private:
    _CharType m_str[_CharArraySize];
    std::size_t m_strLen;
};

using FixedString32 = BasicFixedString<char, 32, StringTraits<char>>;
using FixedString64 = BasicFixedString<char, 64, StringTraits<char>>;
using FixedString128 = BasicFixedString<char, 128, StringTraits<char>>;

using FixedWString32 = BasicFixedString<wchar_t, 32, StringTraits<wchar_t>>;
using FixedWString64 = BasicFixedString<wchar_t, 64, StringTraits<wchar_t>>;
using FixedWString128 = BasicFixedString<wchar_t, 128, StringTraits<wchar_t>>;

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
constexpr BasicFixedString<_CharType, _CharArraySize, StringTraits>::BasicFixedString() noexcept :
    m_str{},
    m_strLen(0)
{
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize, StringTraits>::BasicFixedString(const _CharType(&str)[_CharArraySize2]) :
    BasicFixedString(str, _CharArraySize2 - 1)
{
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline BasicFixedString<_CharType, _CharArraySize, StringTraits>::BasicFixedString(const _CharType* str, std::size_t strLen) :
    StringTraits(str, strLen, m_str, _CharArraySize),
    m_strLen(strLen)
{
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline BasicFixedString<_CharType, _CharArraySize, StringTraits>::BasicFixedString(std::size_t chCount, _CharType ch) :
    StringTraits(m_str, _CharArraySize, ch, chCount),
    m_strLen(chCount)
{
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize, StringTraits>::BasicFixedString(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs) :
    BasicFixedString(rhs.CStr(), rhs.Length())
{
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize, StringTraits>& BasicFixedString<_CharType, _CharArraySize, StringTraits>::operator=(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs)
{
    StringTraits::Assign(rhs.CStr(), rhs.Length());
    return *this;
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize, StringTraits> BasicFixedString<_CharType, _CharArraySize, StringTraits>::operator+(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs) const
{
    return (BasicFixedString<_CharType, _CharArraySize, StringTraits>(*this) += rhs);
}

template<typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template<std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize, StringTraits> BasicFixedString<_CharType, _CharArraySize, StringTraits>::operator+(const _CharType(&rhs)[_CharArraySize2])
{
    return (BasicFixedString<_CharType, _CharArraySize, StringTraits>(*this) += rhs);
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline BasicFixedString<_CharType, _CharArraySize, StringTraits> BasicFixedString<_CharType, _CharArraySize, StringTraits>::operator+(_CharType ch) const
{
    return (BasicFixedString<_CharType, _CharArraySize, StringTraits>(*this) += ch);
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize, StringTraits>& BasicFixedString<_CharType, _CharArraySize, StringTraits>::operator+=(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs)
{
    this->Append(rhs.CStr(), rhs.Length());
    return *this;
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize, StringTraits>& BasicFixedString<_CharType, _CharArraySize, StringTraits>::operator+=(const _CharType(&rhs)[_CharArraySize2])
{
    this->Append(rhs, _CharArraySize2 - 1);
    return *this;
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline BasicFixedString<_CharType, _CharArraySize, StringTraits>& BasicFixedString<_CharType, _CharArraySize, StringTraits>::operator+=(_CharType ch)
{
    this->Append(1, ch);
    return *this;
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template <std::size_t _CharArraySize2>
inline bool BasicFixedString<_CharType, _CharArraySize, StringTraits>::operator==(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs) const
{
	return StringTraits::Compare(m_str, m_strLen, rhs.CStr(), rhs.Length()) == 0;
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline _CharType BasicFixedString<_CharType, _CharArraySize, StringTraits>::operator[](std::size_t index) const
{
	return m_str[index];
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline _CharType& BasicFixedString<_CharType, _CharArraySize, StringTraits>::operator[](std::size_t index)
{
	return m_str[index];
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize + _CharArraySize2, StringTraits> BasicFixedString<_CharType, _CharArraySize, StringTraits>::Expand(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs) const
{
	BasicFixedString<_CharType, _CharArraySize + _CharArraySize2, StringTraits> ret = *this;
	ret += rhs;

	return ret;
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template <std::size_t _CharArraySize2>
inline void BasicFixedString<_CharType, _CharArraySize, StringTraits>::Append(const _CharType(&str)[_CharArraySize2])
{
    this->Append(str, _CharArraySize2 - 1);
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline void BasicFixedString<_CharType, _CharArraySize, StringTraits>::Append(const _CharType* str, std::size_t strLen)
{
    StringTraits::Append(str, strLen, m_str, m_strLen, _CharArraySize);
    m_strLen += strLen;
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline void BasicFixedString<_CharType, _CharArraySize, StringTraits>::Append(std::size_t chCount, _CharType ch)
{
    StringTraits::Append(m_str, m_strLen, _CharArraySize, ch, chCount);
    m_strLen += chCount;
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template <std::size_t _CharArraySize2>
inline void BasicFixedString<_CharType, _CharArraySize, StringTraits>::Assign(const _CharType(&str)[_CharArraySize2])
{
    new (this) BasicFixedString(str);
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline void BasicFixedString<_CharType, _CharArraySize, StringTraits>::Assign(const _CharType* str, std::size_t strLen)
{
    new (this) BasicFixedString(str, strLen);
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline void BasicFixedString<_CharType, _CharArraySize, StringTraits>::Assign(std::size_t chCount, _CharType ch)
{
    new (this) BasicFixedString(chCount, ch);
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template <std::size_t _CharArraySize2>
inline int32_t BasicFixedString<_CharType, _CharArraySize, StringTraits>::Compare(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs) const
{
    return StringTraits::Compare(m_str, m_strLen, rhs.CStr(), rhs.Length());
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template <std::size_t _CharArraySize2>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, StringTraits>::Find(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs) const
{
    return StringTraits::Find(m_str, m_strLen, 0, rhs.CStr(), rhs.Length());
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, StringTraits>::Find(const BasicFixedString& rhs) const
{
    return StringTraits::Find(m_str, m_strLen, 0, rhs.CStr(), rhs.Length());
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, StringTraits>::Find(_CharType ch, std::size_t strOffset) const
{
	return StringTraits::Find(m_str, m_strLen, strOffset, &ch, 1);
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template <std::size_t _CharArraySize2>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, StringTraits>::Find(const _CharType(&str)[_CharArraySize2], std::size_t strOffset) const
{
    return StringTraits::Find(m_str, m_strLen, strOffset, str, _CharArraySize2 - 1);
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, StringTraits>::Find(const _CharType* str, std::size_t strOffset, std::size_t strLen) const
{
    return StringTraits::Find(m_str, m_strLen, strOffset, str, strLen);
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template <std::size_t _CharArraySize2>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, StringTraits>::RFind(const BasicFixedString<_CharType, _CharArraySize2, StringTraits>& rhs) const
{
    return StringTraits::RFind(m_str, m_strLen, 0, rhs.CStr(), rhs.Length());
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, StringTraits>::RFind(const BasicFixedString& rhs) const
{
    return StringTraits::RFind(m_str, m_strLen, 0, rhs.CStr(), rhs.Length());
}

template<typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, StringTraits>::RFind(_CharType ch, std::size_t strOffset) const
{
    return StringTraits::RFind(m_str, m_strLen, strOffset, &ch, 1);
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
template <std::size_t _CharArraySize2>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, StringTraits>::RFind(const _CharType(&str)[_CharArraySize2], std::size_t strOffset) const
{
    return StringTraits::RFind(m_str, m_strLen, strOffset, str, _CharArraySize2 - 1);
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, StringTraits>::RFind(const _CharType* str, std::size_t strOffset, std::size_t strLen) const
{
    return StringTraits::RFind(m_str, m_strLen, strOffset, str, strLen);
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline void BasicFixedString<_CharType, _CharArraySize, StringTraits>::Swap(BasicFixedString& rhs)
{
    if (rhs != this)
    {
        m_str.swap(rhs.m_str);
        std::swap(m_strLen, rhs.m_strLen);
    }
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline const _CharType* BasicFixedString<_CharType, _CharArraySize, StringTraits>::CStr() const noexcept
{
    return m_str;
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline std::size_t BasicFixedString<_CharType, _CharArraySize, StringTraits>::Length() const noexcept
{
    return m_strLen;
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
constexpr std::size_t BasicFixedString<_CharType, _CharArraySize, StringTraits>::Capacity() const noexcept
{
    return _CharArraySize;
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline typename BasicFixedString<_CharType, _CharArraySize, StringTraits>::IteratorType BasicFixedString<_CharType, _CharArraySize, StringTraits>::begin() noexcept
{
    return &m_str[0];
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline typename BasicFixedString<_CharType, _CharArraySize, StringTraits>::IteratorType BasicFixedString<_CharType, _CharArraySize, StringTraits>::end()
{
    return &m_str[m_strLen];
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline typename BasicFixedString<_CharType, _CharArraySize, StringTraits>::ConstIteratorType BasicFixedString<_CharType, _CharArraySize, StringTraits>::cbegin() const noexcept
{
    return &m_str[0];
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline typename BasicFixedString<_CharType, _CharArraySize, StringTraits>::ConstIteratorType BasicFixedString<_CharType, _CharArraySize, StringTraits>::cend() const
{
    return &m_str[m_strLen];
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline typename BasicFixedString<_CharType, _CharArraySize, StringTraits>::ReverseIteratorType BasicFixedString<_CharType, _CharArraySize, StringTraits>::rbegin()
{
    return {this->end()};
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline typename BasicFixedString<_CharType, _CharArraySize, StringTraits>::ReverseIteratorType BasicFixedString<_CharType, _CharArraySize, StringTraits>::rend() noexcept
{
    return {this->begin()};
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline typename BasicFixedString<_CharType, _CharArraySize, StringTraits>::ConstReverseIteratorType BasicFixedString<_CharType, _CharArraySize, StringTraits>::rbegin() const
{
    return {this->end()};
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline typename BasicFixedString<_CharType, _CharArraySize, StringTraits>::ConstReverseIteratorType BasicFixedString<_CharType, _CharArraySize, StringTraits>::rend() const noexcept
{
    return {this->begin()};
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline _CharType& BasicFixedString<_CharType, _CharArraySize, StringTraits>::At(std::size_t index)
{
    assert(index <= m_strLen && "BasicFixedString index out of range");

    return m_str[index];
}

template <typename _CharType, std::size_t _CharArraySize, typename StringTraits>
inline const _CharType BasicFixedString<_CharType, _CharArraySize, StringTraits>::At(std::size_t index) const
{
    assert(index <= m_strLen && "BasicFixedString index out of range");

    return m_str[index];
}

} /* namespace string */
} /* namespace tgon */