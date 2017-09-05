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

template <typename _CharType, std::size_t _CharArraySize>
class BasicFixedString :
    private StringTraits<_CharType>
{
    static_assert(_CharArraySize > 0, "The array size of BasicFixedString must be over than 0.");

/* @section Public type */
public:
    using SizeType = decltype(_CharArraySize);

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
    using StringTraits<_CharType>::StringTraits;

    constexpr BasicFixedString() noexcept = default;
    template <std::size_t _CharArraySize2>
    constexpr BasicFixedString(const _CharType(&str)[_CharArraySize2]);
    constexpr BasicFixedString(const _CharType* str, std::size_t length);
    constexpr BasicFixedString(std::size_t length, _CharType ch);

    template <std::size_t _CharArraySize2>
    BasicFixedString(const BasicFixedString<_CharType, _CharArraySize2>& rhs);

/* @section Public operator */
public:
    template <std::size_t _CharArraySize2>
    BasicFixedString& operator=(const BasicFixedString<_CharType, _CharArraySize2>& rhs);
    BasicFixedString& operator=(const BasicFixedString& rhs) = default;

    template <std::size_t _CharArraySize2>
    BasicFixedString operator+(const BasicFixedString<_CharType, _CharArraySize2>& rhs) const;
    BasicFixedString operator+(_CharType ch) const;

    template <std::size_t _CharArraySize2>
    BasicFixedString& operator+=(const BasicFixedString<_CharType, _CharArraySize2>& rhs);
    BasicFixedString& operator+=(const BasicFixedString& rhs);
    BasicFixedString& operator+=(_CharType ch);

    template <std::size_t _CharArraySize2>
    bool operator==(const BasicFixedString<_CharType, _CharArraySize2>& rhs) const;

    _CharType operator[](std::size_t index) const;
    _CharType& operator[](std::size_t index);

/* @section Public method */
public:
    template <std::size_t _CharArraySize2>
    BasicFixedString<_CharType, _CharArraySize + _CharArraySize2> Extend(const BasicFixedString<_CharType, _CharArraySize2>& rhs) const;

    template <std::size_t _CharArraySize2>
    void Assign(const _CharType(&str)[_CharArraySize2]);
    void Assign(const _CharType* str, std::size_t length);
    void Assign(std::size_t length, _CharType ch);

    template <std::size_t _CharArraySize2>
    int32_t Compare(const BasicFixedString<_CharType, _CharArraySize2>& rhs) const;

    template <std::size_t _CharArraySize2>
    std::size_t Find(const BasicFixedString<_CharType, _CharArraySize2>& rhs) const;
    std::size_t Find(const BasicFixedString& rhs) const;
    std::size_t Find(_CharType ch, std::size_t offset = 0) const;
    template <std::size_t _CharArraySize2>
    std::size_t Find(const _CharType(&str)[_CharArraySize2], std::size_t offset = 0) const;
    std::size_t Find(const _CharType* str, std::size_t offset, std::size_t strLen) const;

    // Todo: need test
    template <std::size_t _CharArraySize2>
    std::size_t Rfind(const BasicFixedString<_CharType, _CharArraySize2>& rhs) const;
    std::size_t Rfind(const BasicFixedString& rhs) const;
    std::size_t Rfind(_CharType ch, std::size_t offset = 0) const;
    template <std::size_t _CharArraySize2>
    std::size_t Rfind(const _CharType(&str)[_CharArraySize2], std::size_t offset = 0) const;
    std::size_t Rfind(const _CharType* str, std::size_t offset, std::size_t count) const;

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

/* @section Public variable */
public:
    using StringTraits<_CharType>::NPos;

/* @section Private variable */
private:
    std::size_t m_length;

    _CharType m_str[_CharArraySize];
};

using FixedString32 = BasicFixedString<char, 32>;
using FixedWString32 = BasicFixedString<wchar_t, 32>;

using FixedString64 = BasicFixedString<char, 64>;
using FixedWString64 = BasicFixedString<wchar_t, 64>;

using FixedString128 = BasicFixedString<char, 128>;
using FixedWString128 = BasicFixedString<wchar_t, 128>;

template <typename _CharType, std::size_t _CharArraySize>
template <std::size_t _CharArraySize2>
constexpr BasicFixedString<_CharType, _CharArraySize>::BasicFixedString(const _CharType(&str)[_CharArraySize2]) :
    BasicFixedString(str, _CharArraySize2 - 1)
{
}

template <typename _CharType, std::size_t _CharArraySize>
constexpr BasicFixedString<_CharType, _CharArraySize>::BasicFixedString(const _CharType* str, std::size_t length) :
    StringTraits<_CharType>(str, m_str, length),
    m_length(length)
{
    //assert(_CharArraySize > length && "BasicFixedString buffer overflowed");
}

template <typename _CharType, std::size_t _CharArraySize>
constexpr BasicFixedString<_CharType, _CharArraySize>::BasicFixedString(std::size_t length, _CharType ch) :
    StringTraits<_CharType>(m_str, _CharArraySize, ch, length),
    m_length(length)
{
}

template <typename _CharType, std::size_t _CharArraySize>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize>::BasicFixedString(const BasicFixedString<_CharType, _CharArraySize2>& rhs) :
    BasicFixedString(rhs.CStr(), _CharArraySize2 - 1)
{
}

template <typename _CharType, std::size_t _CharArraySize>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize>& BasicFixedString<_CharType, _CharArraySize>::operator=(const BasicFixedString<_CharType, _CharArraySize2>& rhs)
{
    StringTraits<_CharType>::Assign(rhs.CStr(), rhs.Length());

    return *this;
}

template <typename _CharType, std::size_t _CharArraySize>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize> BasicFixedString<_CharType, _CharArraySize>::operator+(const BasicFixedString<_CharType, _CharArraySize2>& rhs) const
{
    assert(_CharArraySize > m_length + rhs.Length() && "BasicFixedString buffer overflowed");

    BasicFixedString<_CharType, _CharArraySize> ret = *this;
    ret += rhs;

    return ret;
}

template <typename _CharType, std::size_t _CharArraySize>
inline BasicFixedString<_CharType, _CharArraySize> BasicFixedString<_CharType, _CharArraySize>::operator+(_CharType ch) const
{
    assert(_CharArraySize > m_length + 1 && "BasicFixedString buffer overflowed");

    BasicFixedString<_CharType, _CharArraySize> ret = *this;
    ret[m_length] = ch;
    ret[++m_length] = static_cast<_CharType>(0);
    
    return ret;
}

template <typename _CharType, std::size_t _CharArraySize>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize>& BasicFixedString<_CharType, _CharArraySize>::operator+=(const BasicFixedString<_CharType, _CharArraySize2>& rhs)
{
    assert(_CharArraySize > m_length + rhs.Length() && "BasicFixedString buffer overflowed");

    std::memcpy(&m_str[m_length], rhs.CStr(), sizeof(_CharType) * (rhs.Length() + 1));

    m_length += rhs.Length();

    return *this;
}

template <typename _CharType, std::size_t _CharArraySize>
inline BasicFixedString<_CharType, _CharArraySize>& BasicFixedString<_CharType, _CharArraySize>::operator+=(const BasicFixedString& rhs)
{
	assert(_CharArraySize > m_length + rhs.m_length && "BasicFixedString buffer overflowed");

	std::memcpy(&m_str[m_length], rhs.m_str, sizeof(_CharType) * (rhs.m_length + 1));

	m_length += rhs.m_length;

	return *this;
}

template <typename _CharType, std::size_t _CharArraySize>
inline BasicFixedString<_CharType, _CharArraySize>& BasicFixedString<_CharType, _CharArraySize>::operator+=(_CharType ch)
{
    assert(_CharArraySize > m_length + 1 && "BasicFixedString buffer overflowed");

    m_str[m_length] = ch;
    m_str[++m_length] = static_cast<_CharType>(0);
    
    return *this;
}

template <typename _CharType, std::size_t _CharArraySize>
template <std::size_t _CharArraySize2>
inline bool BasicFixedString<_CharType, _CharArraySize>::operator==(const BasicFixedString<_CharType, _CharArraySize2>& rhs) const
{
	return StringTraits<_CharType>::Compare(m_str, m_length, rhs.CStr(), rhs.Length()) == 0;
}

template <typename _CharType, std::size_t _CharArraySize>
inline _CharType BasicFixedString<_CharType, _CharArraySize>::operator[](std::size_t index) const
{
	return m_str[index];
}

template <typename _CharType, std::size_t _CharArraySize>
inline _CharType& BasicFixedString<_CharType, _CharArraySize>::operator[](std::size_t index)
{
	return m_str[index];
}

template <typename _CharType, std::size_t _CharArraySize>
template <std::size_t _CharArraySize2>
inline BasicFixedString<_CharType, _CharArraySize + _CharArraySize2> BasicFixedString<_CharType, _CharArraySize>::Extend(const BasicFixedString<_CharType, _CharArraySize2>& rhs) const
{
	BasicFixedString<_CharType, _CharArraySize + _CharArraySize2> ret = *this;
	ret += rhs;

	return ret;
}

template <typename _CharType, std::size_t _CharArraySize>
template <std::size_t _CharArraySize2>
inline void BasicFixedString<_CharType, _CharArraySize>::Assign(const _CharType(&str)[_CharArraySize2])
{
    new (this) BasicFixedString(str);
}

template <typename _CharType, std::size_t _CharArraySize>
inline void BasicFixedString<_CharType, _CharArraySize>::Assign(const _CharType* str, std::size_t length)
{
    new (this) BasicFixedString(str, length);
}

template <typename _CharType, std::size_t _CharArraySize>
inline void BasicFixedString<_CharType, _CharArraySize>::Assign(std::size_t length, _CharType ch)
{
    new (this) BasicFixedString(length, ch);
}

template <typename _CharType, std::size_t _CharArraySize>
template <std::size_t _CharArraySize2>
inline int32_t BasicFixedString<_CharType, _CharArraySize>::Compare(const BasicFixedString<_CharType, _CharArraySize2>& rhs) const
{
    return StringTraits<_CharType>::Compare(m_str, m_length, rhs.CStr(), rhs.Length());
}

template <typename _CharType, std::size_t _CharArraySize>
template <std::size_t _CharArraySize2>
inline std::size_t BasicFixedString<_CharType, _CharArraySize>::Find(const BasicFixedString<_CharType, _CharArraySize2>& rhs) const
{
    return StringTraits<_CharType>::Find(m_str, m_length, rhs.CStr(), 0, rhs.Length());
}

template <typename _CharType, std::size_t _CharArraySize>
inline std::size_t BasicFixedString<_CharType, _CharArraySize>::Find(const BasicFixedString& rhs) const
{
    return StringTraits<_CharType>::Find(m_str, m_length, rhs.CStr(), 0, rhs.Length());
}

template <typename _CharType, std::size_t _CharArraySize>
inline std::size_t BasicFixedString<_CharType, _CharArraySize>::Find(_CharType ch, std::size_t offset) const
{
	return StringTraits<_CharType>::Find(m_str, m_length, &ch, offset, 1);
}

template <typename _CharType, std::size_t _CharArraySize>
template <std::size_t _CharArraySize2>
inline std::size_t BasicFixedString<_CharType, _CharArraySize>::Find(const _CharType(&str)[_CharArraySize2], std::size_t offset) const
{
    return StringTraits<_CharType>::Find(m_str, m_length, str, offset, _CharArraySize2 - 1);
}

template <typename _CharType, std::size_t _CharArraySize>
inline std::size_t BasicFixedString<_CharType, _CharArraySize>::Find(const _CharType* str, std::size_t offset, std::size_t count) const
{
    return StringTraits<_CharType>::Find(m_str, m_length, str, offset, count);
}

template <typename _CharType, std::size_t _CharArraySize>
template <std::size_t _CharArraySize2>
inline std::size_t BasicFixedString<_CharType, _CharArraySize>::Rfind(const _CharType(&str)[_CharArraySize2], std::size_t offset) const
{
    if ((offset > m_length) || ((m_length - offset) < _CharArraySize2 - 1))
    {
        return NPos;
    }

    if (_CharArraySize2 == 0)
    {
        return offset;
    }

    // error!!
    const _CharType* foundStr = std::find_end(m_str + offset, m_str.CStr() + m_length, str, str + _CharArraySize2 - 1);
    if (foundStr == m_str + m_length)
    {
        return NPos;
    }

    return static_cast<std::size_t>(&foundStr[0] - &str[0]);
}

template <typename _CharType, std::size_t _CharArraySize>
inline void BasicFixedString<_CharType, _CharArraySize>::Swap(BasicFixedString& rhs)
{
	if (rhs != this)
	{
		m_str.swap(rhs.m_str);
		std::swap(m_length, rhs.m_length);
	}
}

template <typename _CharType, std::size_t _CharArraySize>
inline const _CharType* BasicFixedString<_CharType, _CharArraySize>::CStr() const noexcept
{
	return m_str;
}

template <typename _CharType, std::size_t _CharArraySize>
inline std::size_t BasicFixedString<_CharType, _CharArraySize>::Length() const noexcept
{
	return m_length;
}

template <typename _CharType, std::size_t _CharArraySize>
constexpr std::size_t BasicFixedString<_CharType, _CharArraySize>::Capacity() const noexcept
{
	return _CharArraySize;
}

template <typename _CharType, std::size_t _CharArraySize>
inline typename BasicFixedString<_CharType, _CharArraySize>::IteratorType BasicFixedString<_CharType, _CharArraySize>::begin() noexcept
{
    return &m_str[0];
}

template <typename _CharType, std::size_t _CharArraySize>
inline typename BasicFixedString<_CharType, _CharArraySize>::IteratorType BasicFixedString<_CharType, _CharArraySize>::end()
{
    return &m_str[m_length];
}

template <typename _CharType, std::size_t _CharArraySize>
inline typename BasicFixedString<_CharType, _CharArraySize>::ConstIteratorType BasicFixedString<_CharType, _CharArraySize>::cbegin() const noexcept
{
    return &m_str[0];
}

template <typename _CharType, std::size_t _CharArraySize>
inline typename BasicFixedString<_CharType, _CharArraySize>::ConstIteratorType BasicFixedString<_CharType, _CharArraySize>::cend() const
{
    return &m_str[m_length];
}

template <typename _CharType, std::size_t _CharArraySize>
inline typename BasicFixedString<_CharType, _CharArraySize>::ReverseIteratorType BasicFixedString<_CharType, _CharArraySize>::rbegin()
{
    return {this->end()};
}

template <typename _CharType, std::size_t _CharArraySize>
inline typename BasicFixedString<_CharType, _CharArraySize>::ReverseIteratorType BasicFixedString<_CharType, _CharArraySize>::rend() noexcept
{
    return {this->begin()};
}

template <typename _CharType, std::size_t _CharArraySize>
inline typename BasicFixedString<_CharType, _CharArraySize>::ConstReverseIteratorType BasicFixedString<_CharType, _CharArraySize>::rbegin() const
{
    return {this->end()};
}

template <typename _CharType, std::size_t _CharArraySize>
inline typename BasicFixedString<_CharType, _CharArraySize>::ConstReverseIteratorType BasicFixedString<_CharType, _CharArraySize>::rend() const noexcept
{
    return {this->begin()};
}

template <typename _CharType, std::size_t _CharArraySize>
inline _CharType& BasicFixedString<_CharType, _CharArraySize>::At(std::size_t index)
{
	assert(index <= m_length && "BasicFixedString index out of range");

	return m_str[index];
}

template <typename _CharType, std::size_t _CharArraySize>
inline const _CharType BasicFixedString<_CharType, _CharArraySize>::At(std::size_t index) const
{
	assert(index <= m_length && "BasicFixedString index out of range");

	return m_str[index];
}

} /* namespace string */
} /* namespace tgon */
