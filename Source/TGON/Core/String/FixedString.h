/**
 * @filename    FixedString.h
 * @author      ggomdyu
 * @date        03/16/2017
 */

#pragma once
#include <array>
#include <memory>
#include <cstdint>
#include <cassert>

namespace tgon
{
namespace string
{
namespace detail
{

template <typename _CharType>
class BasicFixedStringImpl
{
/* @section Type definition */
public:
    using CharTraits = std::char_traits<_CharType>;

/* @section Public variable */
public:
    static constexpr std::size_t NPos = static_cast<std::size_t>(-1);

/* @section Public method */
protected:
    static std::size_t FindImpl(const _CharType* srcStr, std::size_t srcStrLength, const _CharType* srcFindStr, std::size_t offset, std::size_t srcFindStrLength);

    static int32_t CompareImpl(const _CharType* lhsStr, std::size_t lhsStrLength, const _CharType* rhsStr, std::size_t rhsStrLength);

    static void AssignImpl(_CharType* destBuffer, std::size_t destBufferSize, _CharType ch, std::size_t chCount);
};

template <typename _CharType>
inline std::size_t BasicFixedStringImpl<_CharType>::FindImpl(const _CharType* srcStr, std::size_t srcStrLength, const _CharType* srcFindStr, std::size_t offset, std::size_t srcFindStrLength)
{
    if ((offset > srcStrLength) || ((srcStrLength - offset) < srcFindStrLength))
    {
        return NPos;
    }

    if (srcFindStrLength == 0)
    {
        return offset;
    }

    const _CharType* foundStr = std::__search(srcStr + offset, srcStr + srcStrLength, srcFindStr, srcFindStr + srcFindStrLength, CharTraits::eq, std::random_access_iterator_tag(), std::random_access_iterator_tag());
    if (foundStr == srcStr + srcStrLength)
    {
        return NPos;
    }

    return static_cast<std::size_t>(foundStr - srcStr);
}

template <typename _CharType>
inline int32_t BasicFixedStringImpl<_CharType>::CompareImpl(const _CharType* lhsStr, std::size_t lhsStrLength, const _CharType* rhsStr, std::size_t rhsStrLength)
{
    auto minSize = lhsStrLength < rhsStrLength ? lhsStrLength : rhsStrLength;

    auto ans = std::char_traits<_CharType>::compare(lhsStr, rhsStr, minSize);
    if (ans != 0)
    {
        return ans;
    }

    if (lhsStrLength < rhsStrLength)
    {
        return -1;
    }
    if (lhsStrLength > rhsStrLength)
    {
        return 1;
    }
    
    return 0;
}

template <typename _CharType>
inline void BasicFixedStringImpl<_CharType>::AssignImpl(_CharType* destBuffer, std::size_t destBufferSize, _CharType ch, std::size_t chCount)
{
    assert(destBufferSize > chCount && "BasicFixedString buffer overflowed");

    std::size_t i = 0;
    while (i < chCount)
    {
		destBuffer[i++] = ch;
    }

	destBuffer[i] = static_cast<_CharType>(0);
}

} /* namespace detail */

template <typename _CharType, std::size_t _Capacity>
class BasicFixedString :
    private detail::BasicFixedStringImpl<_CharType>
{
    static_assert(_Capacity > 0, "The array size of BasicFixedString must be over than 0.");

/* @section Type definition */
public:
    using CharTraits = std::char_traits<_CharType>;

    using SizeType = decltype(_Capacity);

    using ValueType = _CharType;
    using ReferenceType = ValueType&;
    using ConstReferenceType = const ValueType&;
    using IteratorType = ValueType*;
    using ConstIteratorType = const ValueType*;
    using PointerType = ValueType*;
    using ConstPointerType = const ValueType*;
    using ReverseIteratorType = std::reverse_iterator<IteratorType>;
    using ConstReverseIteratorType = std::reverse_iterator<ConstIteratorType>;

/* @section Ctor/Dtor */
public:
    constexpr BasicFixedString() noexcept = default;
    template <std::size_t _Capacity2>
    BasicFixedString(const _CharType(&str)[_Capacity2]);
    BasicFixedString(const _CharType* str, std::size_t length);
    BasicFixedString(std::size_t length, _CharType ch);

    template <std::size_t _Capacity2>
    BasicFixedString(const BasicFixedString<_CharType, _Capacity2>& rhs);

/* @section Operator */
public:
    template <std::size_t _Capacity2>
    BasicFixedString& operator=(const BasicFixedString<_CharType, _Capacity2>& rhs);
    BasicFixedString& operator=(const BasicFixedString& rhs) = default;

    template <std::size_t _Capacity2>
    BasicFixedString operator+(const BasicFixedString<_CharType, _Capacity2>& rhs) const;
    BasicFixedString operator+(_CharType ch) const;

    template <std::size_t _Capacity2>
    BasicFixedString& operator+=(const BasicFixedString<_CharType, _Capacity2>& rhs);
    BasicFixedString& operator+=(const BasicFixedString& rhs);
    BasicFixedString& operator+=(_CharType ch);

    template <std::size_t _Capacity2>
    bool operator==(const BasicFixedString<_CharType, _Capacity2>& rhs) const;

    _CharType operator[](std::size_t index) const;
    _CharType& operator[](std::size_t index);

/* @section Public method */
public:
    template <std::size_t _Capacity2>
    BasicFixedString<_CharType, _Capacity + _Capacity2> Extend(const BasicFixedString<_CharType, _Capacity2>& rhs) const;

    template <std::size_t _Capacity2>
    void Assign(const _CharType(&str)[_Capacity2]);
    void Assign(const _CharType* str, std::size_t length);
    void Assign(std::size_t length, _CharType ch);

    template <std::size_t _Capacity2>
    int32_t Compare(const BasicFixedString<_CharType, _Capacity2>& rhs) const;

    template <std::size_t _Capacity2>
    std::size_t Find(const BasicFixedString<_CharType, _Capacity2>& rhs) const;
    std::size_t Find(const BasicFixedString& rhs) const;
    std::size_t Find(_CharType ch, std::size_t offset = 0) const;
    template <std::size_t _Capacity2>
    std::size_t Find(const _CharType(&str)[_Capacity2], std::size_t offset = 0) const;
    std::size_t Find(const _CharType* str, std::size_t offset, std::size_t count) const;

    //    _LIBCPP_INLINE_VISIBILITY
    //    size_type rfind(const basic_string& __str, size_type __pos = npos) const _NOEXCEPT;
    //    size_type rfind(const value_type* __s, size_type __pos, size_type __n) const _NOEXCEPT;
    //    _LIBCPP_INLINE_VISIBILITY
    //    size_type rfind(const value_type* __s, size_type __pos = npos) const _NOEXCEPT;
    //    size_type rfind(value_type __c, size_type __pos = npos) const _NOEXCEPT;


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

    _CharType& At(std::size_t index);
    const _CharType At(std::size_t index) const;

/* @section Public variable */
public:
    using detail::BasicFixedStringImpl<_CharType>::NPos;

/* @section Private variable */
private:
    std::size_t m_length;

    std::array<_CharType, _Capacity> m_str;
};

using FixedString32 = BasicFixedString<char, 32>;
using FixedWString32 = BasicFixedString<wchar_t, 32>;

using FixedString64 = BasicFixedString<char, 64>;
using FixedWString64 = BasicFixedString<wchar_t, 64>;

using FixedString128 = BasicFixedString<char, 128>;
using FixedWString128 = BasicFixedString<wchar_t, 128>;

template <typename _CharType, std::size_t _Capacity>
template <std::size_t _Capacity2>
inline BasicFixedString<_CharType, _Capacity>::BasicFixedString(const _CharType(&str)[_Capacity2]) :
    BasicFixedString(str, _Capacity2 - 1)
{
}

template <typename _CharType, std::size_t _Capacity>
inline BasicFixedString<_CharType, _Capacity>::BasicFixedString(const _CharType* str, std::size_t length) :
    m_length(length)
{
    assert(_Capacity > length && "BasicFixedString buffer overflowed");

    std::memcpy(m_str.data(), str, sizeof(_CharType) * (length + 1));
}

template <typename _CharType, std::size_t _Capacity>
inline BasicFixedString<_CharType, _Capacity>::BasicFixedString(std::size_t length, _CharType ch) :
    m_length(length)
{
    this->AssignImpl(m_str.data(), _Capacity, ch, length);
}

template <typename _CharType, std::size_t _Capacity>
template <std::size_t _Capacity2>
inline BasicFixedString<_CharType, _Capacity>::BasicFixedString(const BasicFixedString<_CharType, _Capacity2>& rhs) :
    BasicFixedString(rhs.CStr(), _Capacity2 - 1)
{
}

template <typename _CharType, std::size_t _Capacity>
template <std::size_t _Capacity2>
inline BasicFixedString<_CharType, _Capacity>& BasicFixedString<_CharType, _Capacity>::operator=(const BasicFixedString<_CharType, _Capacity2>& rhs)
{
    this->Assign(rhs.CStr(), rhs.Length());

    return *this;
}

template <typename _CharType, std::size_t _Capacity>
template <std::size_t _Capacity2>
inline BasicFixedString<_CharType, _Capacity> BasicFixedString<_CharType, _Capacity>::operator+(const BasicFixedString<_CharType, _Capacity2>& rhs) const
{
    assert(_Capacity > m_length + rhs.Length() && "BasicFixedString buffer overflowed");

    BasicFixedString<_CharType, _Capacity> ret = *this;
    ret += rhs;

    return ret;
}

template <typename _CharType, std::size_t _Capacity>
inline BasicFixedString<_CharType, _Capacity> BasicFixedString<_CharType, _Capacity>::operator+(_CharType ch) const
{
    assert(_Capacity > m_length + 1 && "BasicFixedString buffer overflowed");

    BasicFixedString<_CharType, _Capacity> ret = *this;
    ret[m_length] = ch;
    ret[++m_length] = static_cast<_CharType>(0);
    
    return ret;
}

template <typename _CharType, std::size_t _Capacity>
template <std::size_t _Capacity2>
inline BasicFixedString<_CharType, _Capacity>& BasicFixedString<_CharType, _Capacity>::operator+=(const BasicFixedString<_CharType, _Capacity2>& rhs)
{
    assert(_Capacity > m_length + rhs.Length() && "BasicFixedString buffer overflowed");

    std::memcpy(&m_str[m_length], rhs.CStr(), sizeof(_CharType) * (rhs.Length() + 1));

    m_length += rhs.Length();

    return *this;
}

template <typename _CharType, std::size_t _Capacity>
inline BasicFixedString<_CharType, _Capacity>& BasicFixedString<_CharType, _Capacity>::operator+=(const BasicFixedString& rhs)
{
	assert(_Capacity > m_length + rhs.Length() && "BasicFixedString buffer overflowed");

	std::memcpy(&m_str[m_length], rhs.m_str.data(), sizeof(_CharType) * (rhs.m_length + 1));

	m_length += rhs.m_length;

	return *this;
}

template <typename _CharType, std::size_t _Capacity>
inline BasicFixedString<_CharType, _Capacity>& BasicFixedString<_CharType, _Capacity>::operator+=(_CharType ch)
{
    assert(_Capacity > m_length + 1 && "BasicFixedString buffer overflowed");

    m_str[m_length] = ch;
    m_str[++m_length] = static_cast<_CharType>(0);
    
    return *this;
}

template <typename _CharType, std::size_t _Capacity>
template <std::size_t _Capacity2>
inline bool BasicFixedString<_CharType, _Capacity>::operator==(const BasicFixedString<_CharType, _Capacity2>& rhs) const
{
	return this->CompareImpl(m_str.data(), m_length, rhs.CStr(), rhs.Length()) == 0;
}

template <typename _CharType, std::size_t _Capacity>
inline _CharType BasicFixedString<_CharType, _Capacity>::operator[](std::size_t index) const
{
	return m_str[index];
}

template <typename _CharType, std::size_t _Capacity>
inline _CharType& BasicFixedString<_CharType, _Capacity>::operator[](std::size_t index)
{
	return m_str[index];
}

template <typename _CharType, std::size_t _Capacity>
template <std::size_t _Capacity2>
inline BasicFixedString<_CharType, _Capacity + _Capacity2> BasicFixedString<_CharType, _Capacity>::Extend(const BasicFixedString<_CharType, _Capacity2>& rhs) const
{
	BasicFixedString<_CharType, _Capacity + _Capacity2> ret = *this;
	ret += rhs;

	return ret;
}

template <typename _CharType, std::size_t _Capacity>
template <std::size_t _Capacity2>
inline void BasicFixedString<_CharType, _Capacity>::Assign(const _CharType(&str)[_Capacity2])
{
    new (this) BasicFixedString(str);
}

template <typename _CharType, std::size_t _Capacity>
inline void BasicFixedString<_CharType, _Capacity>::Assign(const _CharType* str, std::size_t length)
{
    new (this) BasicFixedString(str, length);
}

template <typename _CharType, std::size_t _Capacity>
inline void BasicFixedString<_CharType, _Capacity>::Assign(std::size_t length, _CharType ch)
{
    new (this) BasicFixedString(length, ch);
}

template <typename _CharType, std::size_t _Capacity>
template <std::size_t _Capacity2>
inline int32_t BasicFixedString<_CharType, _Capacity>::Compare(const BasicFixedString<_CharType, _Capacity2>& rhs) const
{
    return this->CompareImpl(m_str.data(), m_str.Length(), rhs.data(), rhs.Length());
}

template <typename _CharType, std::size_t _Capacity>
template <std::size_t _Capacity2>
inline std::size_t BasicFixedString<_CharType, _Capacity>::Find(const BasicFixedString<_CharType, _Capacity2>& rhs) const
{
    return this->FindImpl(m_str.data(), m_length, rhs.CStr(), 0, rhs.Length());
}

template <typename _CharType, std::size_t _Capacity>
inline std::size_t BasicFixedString<_CharType, _Capacity>::Find(const BasicFixedString& rhs) const
{
    return this->FindImpl(m_str.data(), m_length, rhs.CStr(), 0, rhs.Length());
}

template <typename _CharType, std::size_t _Capacity>
inline std::size_t BasicFixedString<_CharType, _Capacity>::Find(_CharType ch, std::size_t offset) const
{
	return this->FindImpl(m_str.data(), m_length, &ch, offset, 1);
}

template <typename _CharType, std::size_t _Capacity>
template <std::size_t _Capacity2>
inline std::size_t BasicFixedString<_CharType, _Capacity>::Find(const _CharType(&str)[_Capacity2], std::size_t offset) const
{
    return this->FindImpl(m_str.data(), m_length, str, offset, _Capacity2 - 1);
}

template <typename _CharType, std::size_t _Capacity>
inline std::size_t BasicFixedString<_CharType, _Capacity>::Find(const _CharType* str, std::size_t offset, std::size_t count) const
{
    return this->FindImpl(m_str.data(), m_length, str, offset, count);
}

template <typename _CharType, std::size_t _Capacity>
inline void BasicFixedString<_CharType, _Capacity>::Swap(BasicFixedString& rhs)
{
	if (rhs != this)
	{
		m_str.swap(rhs.m_str);
		std::swap(m_length, rhs.m_length);
	}
}

template <typename _CharType, std::size_t _Capacity>
inline const _CharType* BasicFixedString<_CharType, _Capacity>::CStr() const noexcept
{
	return m_str.data();
}

template <typename _CharType, std::size_t _Capacity>
inline std::size_t string::BasicFixedString<_CharType, _Capacity>::Length() const noexcept
{
	return m_length;
}

template <typename _CharType, std::size_t _Capacity>
constexpr std::size_t tgon::string::BasicFixedString<_CharType, _Capacity>::Capacity() const noexcept
{
	return _Capacity;
}

template <typename _CharType, std::size_t _Capacity>
inline typename tgon::string::BasicFixedString<_CharType, _Capacity>::IteratorType tgon::string::BasicFixedString<_CharType, _Capacity>::begin() noexcept
{
    return &m_str[0];
}

template <typename _CharType, std::size_t _Capacity>
inline typename tgon::string::BasicFixedString<_CharType, _Capacity>::IteratorType tgon::string::BasicFixedString<_CharType, _Capacity>::end()
{
    return &m_str[m_length];
}

template <typename _CharType, std::size_t _Capacity>
inline typename tgon::string::BasicFixedString<_CharType, _Capacity>::ConstIteratorType tgon::string::BasicFixedString<_CharType, _Capacity>::cbegin() const noexcept
{
    return &m_str[0];
}

template <typename _CharType, std::size_t _Capacity>
inline typename tgon::string::BasicFixedString<_CharType, _Capacity>::ConstIteratorType tgon::string::BasicFixedString<_CharType, _Capacity>::cend() const
{
    return &m_str[m_length];
}

template <typename _CharType, std::size_t _Capacity>
inline typename tgon::string::BasicFixedString<_CharType, _Capacity>::ReverseIteratorType tgon::string::BasicFixedString<_CharType, _Capacity>::rbegin()
{
    return {this->end()};
}

template <typename _CharType, std::size_t _Capacity>
inline typename tgon::string::BasicFixedString<_CharType, _Capacity>::ReverseIteratorType tgon::string::BasicFixedString<_CharType, _Capacity>::rend() noexcept
{
    return {this->begin()};
}

template <typename _CharType, std::size_t _Capacity>
inline typename tgon::string::BasicFixedString<_CharType, _Capacity>::ConstReverseIteratorType tgon::string::BasicFixedString<_CharType, _Capacity>::rbegin() const
{
    return {this->end()};
}

template <typename _CharType, std::size_t _Capacity>
inline typename tgon::string::BasicFixedString<_CharType, _Capacity>::ConstReverseIteratorType tgon::string::BasicFixedString<_CharType, _Capacity>::rend() const noexcept
{
    return {this->begin()};
}

template <typename _CharType, std::size_t _Capacity>
inline _CharType& tgon::string::BasicFixedString<_CharType, _Capacity>::At(std::size_t index)
{
	assert(index <= m_length && "BasicFixedString index out of range");

	return m_str[index];
}

template <typename _CharType, std::size_t _Capacity>
inline const _CharType BasicFixedString<_CharType, _Capacity>::At(std::size_t index) const
{
	assert(index <= m_length && "BasicFixedString index out of range");

	return m_str[index];
}

} /* namespace string */
} /* namespace tgon */