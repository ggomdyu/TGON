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

template <typename CharTy, std::size_t N>
class BasicFixedString
{
    static_assert(N > 0, "The array size of BasicFixedString must be over than 0.");

/**
 * @section Type definition
 */
private:
    using TraitsTy = std::char_traits<CharTy>;
    
    enum : std::size_t
    {
        NPos = static_cast<std::size_t>(-1),
    };
    
/**
 * @section Ctor/Dtor
 */
public:
    constexpr BasicFixedString() noexcept = default;
    template <std::size_t N2>
	BasicFixedString(const CharTy(&str)[N2]);
	BasicFixedString(const CharTy* str, std::size_t length);
	BasicFixedString(std::size_t length, CharTy ch);
    
    template <std::size_t N2>
    BasicFixedString(const BasicFixedString<CharTy, N2>& rhs);

/**
 * @section Operator
 */
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

/**
 * @section Public method
 */
public:
    template <std::size_t N2>
	BasicFixedString<CharTy, N + N2> Extend(const BasicFixedString<CharTy, N2>& rhs) const;
    
    template <std::size_t N2>
	void Assign(const CharTy(&str)[N2]);
	void Assign(const CharTy* str, std::size_t length);
	void Assign(std::size_t length, CharTy ch);
    
    template <std::size_t N2>
	int32_t Compare(const BasicFixedString<CharTy, N2>& rhs) const;
    
	int32_t Find(CharTy ch, std::size_t offset = 0) const;
	int32_t Find(const CharTy* ch, std::size_t offset, std::size_t count) const;
    
	void Swap(BasicFixedString& rhs);
    
	const CharTy* CStr() const noexcept;
    
	std::size_t Length() const noexcept;
    
	constexpr std::size_t Capacity() const noexcept;
    
	CharTy& At(std::size_t index);
	CharTy At(std::size_t index) const;

/**
 * @section Private variable
 */
private:
    std::size_t m_length;
    
    std::array<CharTy, N> m_str;
};

using FixedString = BasicFixedString<char, 32>;
using FixedWString = BasicFixedString<wchar_t, 32>;

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline BasicFixedString<CharTy, N>::BasicFixedString(const CharTy(&str)[N2]) :
    m_length(N2 - 1)
{
    std::memcpy(m_str.data(), str, sizeof(CharTy) * N2);
}

template<typename CharTy, std::size_t N>
inline BasicFixedString<CharTy, N>::BasicFixedString(const CharTy* str, std::size_t length) :
    m_length(length)
{
    // todo: 이하 코드 잘 작동하는지 확인 필요
    assert(N < length && "BasicFixedString buffer overflowed");
    
    std::memcpy(m_str.data(), str, sizeof(CharTy) * (length + 1));
}

template<typename CharTy, std::size_t N>
inline BasicFixedString<CharTy, N>::BasicFixedString(std::size_t length, CharTy ch)
{
	this->Assign(length, ch);
}

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline BasicFixedString<CharTy, N>::BasicFixedString(const BasicFixedString<CharTy, N2>& rhs) :
    BasicFixedString(rhs.CStr(), N2 - 1)
{
}

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline BasicFixedString<CharTy, N>& BasicFixedString<CharTy, N>::operator=(const BasicFixedString<CharTy, N2>& rhs)
{
	this->Assign(rhs.CStr(), rhs.Length());

	return *this;
}

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline BasicFixedString<CharTy, N> BasicFixedString<CharTy, N>::operator+(const BasicFixedString<CharTy, N2>& rhs) const
{
	assert(N > m_length + rhs.Length() && "BasicFixedString buffer overflowed");

    // 표현식 템플릿 적용 필요
	BasicFixedString<CharTy, N> ret = *this;
	ret += rhs;

	return ret;
}

template<typename CharTy, std::size_t N>
inline BasicFixedString<CharTy, N> BasicFixedString<CharTy, N>::operator+(const BasicFixedString& rhs) const
{
	assert(N > m_length + rhs.Length() && "BasicFixedString buffer overflowed");

	BasicFixedString<CharTy, N> ret = *this;
	ret += rhs;

	return ret;
}

template<typename CharTy, std::size_t N>
inline BasicFixedString<CharTy, N> BasicFixedString<CharTy, N>::operator+(CharTy ch) const
{
	m_str[m_length] = ch;
	m_str[++m_length] = static_cast<CharTy>(0);

	return *this;
}

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline BasicFixedString<CharTy, N>& BasicFixedString<CharTy, N>::operator+=(const BasicFixedString<CharTy, N2>& rhs)
{
	assert(N > m_length + rhs.Length() && "BasicFixedString buffer overflowed");

	std::memcpy(&m_str[m_length], rhs.CStr(), sizeof(CharTy) * (rhs.Length() + 1));

	m_length += rhs.Length();

	return *this;
}

template<typename CharTy, std::size_t N>
inline BasicFixedString<CharTy, N>& BasicFixedString<CharTy, N>::operator+=(const BasicFixedString& rhs)
{
	assert(N > m_length + rhs.Length() && "BasicFixedString buffer overflowed");

	std::memcpy(&m_str[m_length], rhs.m_str.data(), sizeof(CharTy) * (rhs.m_length + 1));

	m_length += rhs.m_length;

	return *this;
}

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline bool BasicFixedString<CharTy, N>::operator==(const BasicFixedString<CharTy, N2>& rhs) const
{
	return this->Compare(rhs) == 0;
}

template<typename CharTy, std::size_t N>
inline CharTy BasicFixedString<CharTy, N>::operator[](std::size_t index) const
{
	return m_str[index];
}

template<typename CharTy, std::size_t N>
inline CharTy& BasicFixedString<CharTy, N>::operator[](std::size_t index)
{
	return m_str[index];
}

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline BasicFixedString<CharTy, N + N2> BasicFixedString<CharTy, N>::Extend(const BasicFixedString<CharTy, N2>& rhs) const
{
	BasicFixedString<CharTy, N + N2> ret = *this;
	ret += rhs;

	return ret;
}

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline void BasicFixedString<CharTy, N>::Assign(const CharTy(&str)[N2])
{
    new (this) BasicFixedString(str);
}

template<typename CharTy, std::size_t N>
inline void BasicFixedString<CharTy, N>::Assign(const CharTy* str, std::size_t length)
{
    new (this) BasicFixedString(str, length);
}

template<typename CharTy, std::size_t N>
inline void BasicFixedString<CharTy, N>::Assign(std::size_t length, CharTy ch)
{
	std::size_t i = 0;
	while (i < length)
	{
		m_str[i++] = ch;
	}

	m_str[i] = static_cast<CharTy>(0);
	m_length = length;
}

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline int32_t BasicFixedString<CharTy, N>::Compare(const BasicFixedString<CharTy, N2>& rhs) const
{
	auto minSize = m_length < rhs.Length() ? m_length : rhs.Length();

	auto ans = TraitsTy::compare(m_str.data(), rhs.CStr(), minSize);
	if (ans != 0)
	{
		return ans;
	}

	if (m_length < rhs.Length())
	{
		return -1;
	}
	if (m_length > rhs.Length())
	{
		return 1;
	}

	return 0;
}

template<typename CharTy, std::size_t N>
inline int32_t BasicFixedString<CharTy, N>::Find(CharTy ch, std::size_t offset) const
{
	return this->Find(&ch, offset, 1);
}

template<typename CharTy, std::size_t N>
inline int32_t BasicFixedString<CharTy, N>::Find(const CharTy* ch, std::size_t offset, std::size_t count) const
{
	// TODO: ≈◊Ω∫∆Æ « ø‰
	for (auto i = offset;; ++i)
	{
		auto ans = TraitsTy::compare(&m_str.data()[offset], ch, count);
		if (ans == 0)
		{
			return i;
		}
	}

	return NPos;
}

template<typename CharTy, std::size_t N>
inline void BasicFixedString<CharTy, N>::Swap(BasicFixedString& rhs)
{
	if (rhs != this)
	{
		m_str.swap(rhs.m_str);
		std::swap(m_length, rhs.m_length);
	}
}

template<typename CharTy, std::size_t N>
inline const CharTy* BasicFixedString<CharTy, N>::CStr() const noexcept
{
	return m_str.data();
}

template<typename CharTy, std::size_t N>
inline std::size_t string::BasicFixedString<CharTy, N>::Length() const noexcept
{
	return m_length;
}

template<typename CharTy, std::size_t N>
inline constexpr std::size_t tgon::string::BasicFixedString<CharTy, N>::Capacity() const noexcept
{
	return N;
}

template<typename CharTy, std::size_t N>
inline CharTy& tgon::string::BasicFixedString<CharTy, N>::At(std::size_t index)
{
	assert(index <= m_length && "BasicFixedString index out of range");

	return m_str[index];
}

template<typename CharTy, std::size_t N>
inline CharTy BasicFixedString<CharTy, N>::At(std::size_t index) const
{
	assert(index <= m_length && "BasicFixedString index out of range");

	return m_str[index];
}

} /* namespace string */
} /* namespace tgon */
