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

template <typename CharTy>
class BasicFixedStringImpl
{
/* @section Type definition */
public:
    using TraitsTy = std::char_traits<CharTy>;

/* @section Public variable */
public:
    static constexpr std::size_t NPos = static_cast<std::size_t>(-1);

/* @section Public method */
protected:
    static std::size_t FindImpl(const CharTy* srcStr, std::size_t srcStrLength, const CharTy* srcFindStr, std::size_t offset, std::size_t srcFindStrLength);

    static int32_t CompareImpl(const CharTy* lhsStr, std::size_t lhsStrLength, const CharTy* rhsStr, std::size_t rhsStrLength);
};

template <typename CharTy>
inline std::size_t BasicFixedStringImpl<CharTy>::FindImpl(const CharTy* srcStr, std::size_t srcStrLength, const CharTy* srcFindStr, std::size_t offset, std::size_t srcFindStrLength)
{
    if ((offset > srcStrLength) || (srcStrLength - offset < srcFindStrLength))
    {
        return NPos;
    }

    if (srcFindStrLength == 0)
    {
        return offset;
    }

    const CharTy* foundStr = std::__search(srcStr + offset, srcStr + srcStrLength, srcFindStr, srcFindStr + srcFindStrLength, TraitsTy::eq, std::random_access_iterator_tag(), std::random_access_iterator_tag());
    if (foundStr == srcStr + srcStrLength)
    {
        return NPos;
    }

    return static_cast<std::size_t>(foundStr - srcStr);
}

template <typename CharTy>
inline int32_t BasicFixedStringImpl<CharTy>::CompareImpl(const CharTy* lhsStr, std::size_t lhsStrLength, const CharTy* rhsStr, std::size_t rhsStrLength)
{
    auto minSize = lhsStrLength < rhsStrLength ? lhsStrLength : rhsStrLength;

    auto ans = std::char_traits<CharTy>::compare(lhsStr, rhsStr, minSize);
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

} /* namespace detail */

template <typename CharTy, std::size_t N>
class BasicFixedString :
    private detail::BasicFixedStringImpl<CharTy>
{
    static_assert(N > 0, "The array size of BasicFixedString must be over than 0.");

/* @section Type definition */
public:
    using TraitsTy = std::char_traits<CharTy>;

    using SizeTy = decltype(N);

    using ValueType = CharTy;
    using ReferenceTy = ValueType&;
    using ConstReferenceTy = const ValueType&;
    using IteratorTy = ValueType*;
    using ConstIteratorTy = const ValueType*;
    using PointerTy = ValueType*;
    using ConstPointer = const ValueType*;
    using ReverseIteratorTy = std::reverse_iterator<IteratorTy>;
    using ConstReverseIteratorTy = std::reverse_iterator<ConstIteratorTy>;

/* @section Ctor/Dtor */
public:
    constexpr BasicFixedString() noexcept = default;
    template <std::size_t N2>
    BasicFixedString(const CharTy(&str)[N2]);
    BasicFixedString(const CharTy* str, std::size_t length);
    BasicFixedString(std::size_t length, CharTy ch);

    template <std::size_t N2>
    BasicFixedString(const BasicFixedString<CharTy, N2>& rhs);

/* @section Operator */
public:
    template <std::size_t N2>
    BasicFixedString& operator=(const BasicFixedString<CharTy, N2>& rhs);
    BasicFixedString& operator=(const BasicFixedString& rhs) = default;

    template <std::size_t N2>
    BasicFixedString operator+(const BasicFixedString<CharTy, N2>& rhs) const;
    BasicFixedString operator+(const BasicFixedString& rhs) const;
    BasicFixedString operator+(CharTy ch) const;

    template <std::size_t N2>
    BasicFixedString& operator+=(const BasicFixedString<CharTy, N2>& rhs);
    BasicFixedString& operator+=(const BasicFixedString& rhs);
    BasicFixedString& operator+=(CharTy ch);

    template <std::size_t N2>
    bool operator==(const BasicFixedString<CharTy, N2>& rhs) const;

    CharTy operator[](std::size_t index) const;
    CharTy& operator[](std::size_t index);

/* @section Public method */
public:
    template <std::size_t N2>
    BasicFixedString<CharTy, N + N2> Extend(const BasicFixedString<CharTy, N2>& rhs) const;

    template <std::size_t N2>
    void Assign(const CharTy(&str)[N2]);
    void Assign(const CharTy* str, std::size_t length);
    void Assign(std::size_t length, CharTy ch);

    template <std::size_t N2>
    int32_t Compare(const BasicFixedString<CharTy, N2>& rhs) const;

    template <std::size_t N2>
    std::size_t Find(const BasicFixedString<CharTy, N2>& rhs) const;
    std::size_t Find(const BasicFixedString& rhs) const;
    std::size_t Find(CharTy ch, std::size_t offset = 0) const;
    template <std::size_t N2>
    std::size_t Find(const CharTy(&str)[N2], std::size_t offset = 0) const;
    std::size_t Find(const CharTy* str, std::size_t offset, std::size_t count) const;

    //    _LIBCPP_INLINE_VISIBILITY
    //    size_type rfind(const basic_string& __str, size_type __pos = npos) const _NOEXCEPT;
    //    size_type rfind(const value_type* __s, size_type __pos, size_type __n) const _NOEXCEPT;
    //    _LIBCPP_INLINE_VISIBILITY
    //    size_type rfind(const value_type* __s, size_type __pos = npos) const _NOEXCEPT;
    //    size_type rfind(value_type __c, size_type __pos = npos) const _NOEXCEPT;


    void Swap(BasicFixedString& rhs);

    const CharTy* CStr() const noexcept;

    std::size_t Length() const noexcept;
    constexpr std::size_t Capacity() const noexcept;

    IteratorTy begin() noexcept;
    IteratorTy end();
    ConstIteratorTy cbegin() const noexcept;
    ConstIteratorTy cend() const;
    ReverseIteratorTy rbegin();
    ReverseIteratorTy rend() noexcept;
    ConstReverseIteratorTy rbegin() const;
    ConstReverseIteratorTy rend() const noexcept;

    CharTy& At(std::size_t index);
    const CharTy At(std::size_t index) const;

/* @section Public variable */
public:
    using detail::BasicFixedStringImpl<CharTy>::NPos;

/* @section Private variable */
private:
    std::size_t m_length;

    std::array<CharTy, N> m_str;
};

using FixedString32 = BasicFixedString<char, 32>;
using FixedWString32 = BasicFixedString<wchar_t, 32>;

using FixedString64 = BasicFixedString<char, 64>;
using FixedWString64 = BasicFixedString<wchar_t, 64>;

using FixedString128 = BasicFixedString<char, 128>;
using FixedWString128 = BasicFixedString<wchar_t, 128>;

template <typename CharTy, std::size_t N>
template <std::size_t N2>
inline BasicFixedString<CharTy, N>::BasicFixedString(const CharTy(&str)[N2]) :
    BasicFixedString(str, N2 - 1)
{
}

template <typename CharTy, std::size_t N>
inline BasicFixedString<CharTy, N>::BasicFixedString(const CharTy* str, std::size_t length) :
    m_length(length)
{
    assert(N > length && "BasicFixedString buffer overflowed");

    std::memcpy(m_str.data(), str, sizeof(CharTy) * (length + 1));
}

template <typename CharTy, std::size_t N>
inline BasicFixedString<CharTy, N>::BasicFixedString(std::size_t length, CharTy ch) :
    m_length(length)
{
    assert(N > length && "BasicFixedString buffer overflowed");

    std::size_t i = 0;
    while (i < length)
    {
        m_str[i++] = ch;
    }

    m_str[i] = static_cast<CharTy>(0);
}

template <typename CharTy, std::size_t N>
template <std::size_t N2>
inline BasicFixedString<CharTy, N>::BasicFixedString(const BasicFixedString<CharTy, N2>& rhs) :
    BasicFixedString(rhs.CStr(), N2 - 1)
{
}

template <typename CharTy, std::size_t N>
template <std::size_t N2>
inline BasicFixedString<CharTy, N>& BasicFixedString<CharTy, N>::operator=(const BasicFixedString<CharTy, N2>& rhs)
{
    this->Assign(rhs.CStr(), rhs.Length());

    return *this;
}

template <typename CharTy, std::size_t N>
template <std::size_t N2>
inline BasicFixedString<CharTy, N> BasicFixedString<CharTy, N>::operator+(const BasicFixedString<CharTy, N2>& rhs) const
{
    assert(N > m_length + rhs.Length() && "BasicFixedString buffer overflowed");

    // 표현식 템플릿 적용 필요
    BasicFixedString<CharTy, N> ret = *this;
    ret += rhs;

    return ret;
}

template <typename CharTy, std::size_t N>
inline BasicFixedString<CharTy, N> BasicFixedString<CharTy, N>::operator+(const BasicFixedString& rhs) const
{
    assert(N > m_length + rhs.Length() && "BasicFixedString buffer overflowed");

    // 표현식 템플릿 적용 필요
    BasicFixedString<CharTy, N> ret = *this;
    ret += rhs;

    return ret;
}

template <typename CharTy, std::size_t N>
inline BasicFixedString<CharTy, N> BasicFixedString<CharTy, N>::operator+(CharTy ch) const
{
    m_str[m_length] = ch;
    m_str[++m_length] = static_cast<CharTy>(0);

    return *this;
}

template <typename CharTy, std::size_t N>
template <std::size_t N2>
inline BasicFixedString<CharTy, N>& BasicFixedString<CharTy, N>::operator+=(const BasicFixedString<CharTy, N2>& rhs)
{
    assert(N > m_length + rhs.Length() && "BasicFixedString buffer overflowed");

    std::memcpy(&m_str[m_length], rhs.CStr(), sizeof(CharTy) * (rhs.Length() + 1));

    m_length += rhs.Length();

    return *this;
}

template <typename CharTy, std::size_t N>
inline BasicFixedString<CharTy, N>& BasicFixedString<CharTy, N>::operator+=(const BasicFixedString& rhs)
{
	assert(N > m_length + rhs.Length() && "BasicFixedString buffer overflowed");

	std::memcpy(&m_str[m_length], rhs.m_str.data(), sizeof(CharTy) * (rhs.m_length + 1));

	m_length += rhs.m_length;

	return *this;
}

template <typename CharTy, std::size_t N>
template <std::size_t N2>
inline bool BasicFixedString<CharTy, N>::operator==(const BasicFixedString<CharTy, N2>& rhs) const
{
	return this->CompareImpl(m_str.data(), m_length, rhs.CStr(), rhs.Length()) == 0;
}

template <typename CharTy, std::size_t N>
inline CharTy BasicFixedString<CharTy, N>::operator[](std::size_t index) const
{
	return m_str[index];
}

template <typename CharTy, std::size_t N>
inline CharTy& BasicFixedString<CharTy, N>::operator[](std::size_t index)
{
	return m_str[index];
}

template <typename CharTy, std::size_t N>
template <std::size_t N2>
inline BasicFixedString<CharTy, N + N2> BasicFixedString<CharTy, N>::Extend(const BasicFixedString<CharTy, N2>& rhs) const
{
	BasicFixedString<CharTy, N + N2> ret = *this;
	ret += rhs;

	return ret;
}

template <typename CharTy, std::size_t N>
template <std::size_t N2>
inline void BasicFixedString<CharTy, N>::Assign(const CharTy(&str)[N2])
{
    new (this) BasicFixedString(str);
}

template <typename CharTy, std::size_t N>
inline void BasicFixedString<CharTy, N>::Assign(const CharTy* str, std::size_t length)
{
    new (this) BasicFixedString(str, length);
}

template <typename CharTy, std::size_t N>
inline void BasicFixedString<CharTy, N>::Assign(std::size_t length, CharTy ch)
{
    new (this) BasicFixedString(length, ch);
}

template <typename CharTy, std::size_t N>
template <std::size_t N2>
inline int32_t BasicFixedString<CharTy, N>::Compare(const BasicFixedString<CharTy, N2>& rhs) const
{
    return this->CompareImpl(m_str.data(), m_str.Length(), rhs.data(), rhs.Length());
}

template <typename CharTy, std::size_t N>
template <std::size_t N2>
inline std::size_t BasicFixedString<CharTy, N>::Find(const BasicFixedString<CharTy, N2>& rhs) const
{
    return this->FindImpl(m_str.data(), m_length, rhs.CStr(), 0, rhs.Length());
}

template <typename CharTy, std::size_t N>
inline std::size_t BasicFixedString<CharTy, N>::Find(const BasicFixedString& rhs) const
{
    return this->FindImpl(m_str.data(), m_length, rhs.CStr(), 0, rhs.Length());
}

template <typename CharTy, std::size_t N>
inline std::size_t BasicFixedString<CharTy, N>::Find(CharTy ch, std::size_t offset) const
{
	return this->FindImpl(m_str.data(), m_length, &ch, offset, 1);
}

template <typename CharTy, std::size_t N>
template <std::size_t N2>
inline std::size_t BasicFixedString<CharTy, N>::Find(const CharTy(&str)[N2], std::size_t offset) const
{
    return this->FindImpl(m_str.data(), m_length, str, offset, N2 - 1);
}

template <typename CharTy, std::size_t N>
inline std::size_t BasicFixedString<CharTy, N>::Find(const CharTy* str, std::size_t offset, std::size_t count) const
{
    return this->FindImpl(m_str.data(), m_length, str, offset, count);
}

template <typename CharTy, std::size_t N>
inline void BasicFixedString<CharTy, N>::Swap(BasicFixedString& rhs)
{
	if (rhs != this)
	{
		m_str.swap(rhs.m_str);
		std::swap(m_length, rhs.m_length);
	}
}

template <typename CharTy, std::size_t N>
inline const CharTy* BasicFixedString<CharTy, N>::CStr() const noexcept
{
	return m_str.data();
}

template <typename CharTy, std::size_t N>
inline std::size_t string::BasicFixedString<CharTy, N>::Length() const noexcept
{
	return m_length;
}

template <typename CharTy, std::size_t N>
constexpr std::size_t tgon::string::BasicFixedString<CharTy, N>::Capacity() const noexcept
{
	return N;
}

template <typename CharTy, std::size_t N>
inline typename tgon::string::BasicFixedString<CharTy, N>::IteratorTy tgon::string::BasicFixedString<CharTy, N>::begin() noexcept
{
    return &m_str[0];
}

template <typename CharTy, std::size_t N>
inline typename tgon::string::BasicFixedString<CharTy, N>::IteratorTy tgon::string::BasicFixedString<CharTy, N>::end()
{
    return &m_str[m_length];
}

template <typename CharTy, std::size_t N>
inline typename tgon::string::BasicFixedString<CharTy, N>::ConstIteratorTy tgon::string::BasicFixedString<CharTy, N>::cbegin() const noexcept
{
    return &m_str[0];
}

template <typename CharTy, std::size_t N>
inline typename tgon::string::BasicFixedString<CharTy, N>::ConstIteratorTy tgon::string::BasicFixedString<CharTy, N>::cend() const
{
    return &m_str[m_length];
}

template <typename CharTy, std::size_t N>
inline typename tgon::string::BasicFixedString<CharTy, N>::ReverseIteratorTy tgon::string::BasicFixedString<CharTy, N>::rbegin()
{
    return {this->end()};
}

template <typename CharTy, std::size_t N>
inline typename tgon::string::BasicFixedString<CharTy, N>::ReverseIteratorTy tgon::string::BasicFixedString<CharTy, N>::rend() noexcept
{
    return {this->begin()};
}

template <typename CharTy, std::size_t N>
inline typename tgon::string::BasicFixedString<CharTy, N>::ConstReverseIteratorTy tgon::string::BasicFixedString<CharTy, N>::rbegin() const
{
    return {this->end()};
}

template <typename CharTy, std::size_t N>
inline typename tgon::string::BasicFixedString<CharTy, N>::ConstReverseIteratorTy tgon::string::BasicFixedString<CharTy, N>::rend() const noexcept
{
    return {this->begin()};
}

template <typename CharTy, std::size_t N>
inline CharTy& tgon::string::BasicFixedString<CharTy, N>::At(std::size_t index)
{
	assert(index <= m_length && "BasicFixedString index out of range");

	return m_str[index];
}

template <typename CharTy, std::size_t N>
inline const CharTy BasicFixedString<CharTy, N>::At(std::size_t index) const
{
	assert(index <= m_length && "BasicFixedString index out of range");

	return m_str[index];
}

} /* namespace string */
} /* namespace tgon */
