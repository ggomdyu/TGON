/**
 * @filename    TFixedString.h
 * @author      ggomdyu
 * @date        03/16/2017
 */

#pragma once
#include <array>
#include <memory>
#include <cstdint>
#include <cassert>

namespace tgon {
namespace string {

template <typename CharTy, std::size_t N>
class TBasicFixedString
{
    static_assert(N > 0, "The array size of TBasicFixedString must be over than 0.");

/**
 * @section Type definition
 */
private:
    using TraitsTy = std::char_traits<CharTy>;

/**
 * @section Ctor/Dtor
 */
public:
    constexpr TBasicFixedString() noexcept = default;
    template <std::size_t N2>
	TBasicFixedString(const CharTy(&str)[N2]);
	TBasicFixedString(const CharTy* str, std::size_t length);
	TBasicFixedString(std::size_t length, CharTy ch);
    template <std::size_t N2>
    TBasicFixedString(const TBasicFixedString<CharTy, N2>& rhs);

/**
 * @section Operator
 */
public:
    template <std::size_t N2>
	TBasicFixedString& operator=(const TBasicFixedString<CharTy, N2>& rhs);
    TBasicFixedString& operator=(const TBasicFixedString& rhs) = default;
    template <std::size_t N2>
	TBasicFixedString operator+(const TBasicFixedString<CharTy, N2>& rhs) const;
	TBasicFixedString operator+(const TBasicFixedString& rhs) const;
	TBasicFixedString operator+(CharTy ch) const;
    template <std::size_t N2>
	TBasicFixedString& operator+=(const TBasicFixedString<CharTy, N2>& rhs);
	TBasicFixedString& operator+=(const TBasicFixedString& rhs);
    TBasicFixedString& operator+=(CharTy ch);
    template <std::size_t N2>
	bool operator==(const TBasicFixedString<CharTy, N2>& rhs) const;
	CharTy operator[](std::size_t index) const;
	CharTy& operator[](std::size_t index);

/**
 * @section Public method
 */
public:
    template <std::size_t N2>
	TBasicFixedString<CharTy, N + N2> Extend(const TBasicFixedString<CharTy, N2>& rhs) const;
    template <std::size_t N2>
	void Assign(const CharTy(&str)[N2]);
	void Assign(const CharTy* str, std::size_t length);
	void Assign(std::size_t length, CharTy ch);
    template <std::size_t N2>
	int32_t Compare(const TBasicFixedString<CharTy, N2>& rhs) const;
	int32_t Find(CharTy ch, std::size_t offset = 0) const;
	int32_t Find(const CharTy* ch, std::size_t offset, std::size_t count) const;
	void Swap(TBasicFixedString& rhs);
	const CharTy* CStr() const noexcept;
	std::size_t Length() const noexcept;
	constexpr std::size_t Capacity() const noexcept;
	CharTy& At(std::size_t index);
	CharTy At(std::size_t index) const;

/**
 * @section Public variable
 */
public:
    static const std::size_t NPos = -1;

/**
 * @section Private variable
 */
private:
    std::size_t m_length;

    std::array<CharTy, N> m_str;
};

using TFixedString = TBasicFixedString<char, 32>;
using TFixedWString = TBasicFixedString<wchar_t, 32>;

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline TBasicFixedString<CharTy, N>::TBasicFixedString(const CharTy(&str)[N2])
{
	this->Assign(str);
}

template<typename CharTy, std::size_t N>
inline TBasicFixedString<CharTy, N>::TBasicFixedString(const CharTy* str, std::size_t length)
{
	this->Assign(str, length);
}

template<typename CharTy, std::size_t N>
inline TBasicFixedString<CharTy, N>::TBasicFixedString(std::size_t length, CharTy ch)
{
	this->Assign(length, ch);
}

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline TBasicFixedString<CharTy, N>::TBasicFixedString(const TBasicFixedString<CharTy, N2>& rhs)
{
	assert(N > rhs.Length() && "TBasicFixedString buffer overflowed");

	this->Assign(rhs.CStr(), rhs.Length());
}

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline TBasicFixedString<CharTy, N>& TBasicFixedString<CharTy, N>::operator=(const TBasicFixedString<CharTy, N2>& rhs)
{
	assert(N > rhs.Length() && "TBasicFixedString buffer overflowed");

	this->Assign(rhs.CStr(), rhs.Length());

	return *this;
}

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline TBasicFixedString<CharTy, N> TBasicFixedString<CharTy, N>::operator+(const TBasicFixedString<CharTy, N2>& rhs) const
{
	assert(N > m_length + rhs.Length() && "TBasicFixedString buffer overflowed");

	TBasicFixedString<CharTy, N> ret = *this;
	ret += rhs;

	return ret;
}

template<typename CharTy, std::size_t N>
inline TBasicFixedString<CharTy, N> TBasicFixedString<CharTy, N>::operator+(const TBasicFixedString& rhs) const
{
	assert(N > m_length + rhs.Length() && "TBasicFixedString buffer overflowed");

	TBasicFixedString<CharTy, N> ret = *this;
	ret += rhs;

	return ret;
}

template<typename CharTy, std::size_t N>
inline TBasicFixedString<CharTy, N> TBasicFixedString<CharTy, N>::operator+(CharTy ch) const
{
	m_str[m_length] = ch;
	m_str[++m_length] = static_cast<CharTy>(0);

	return *this;
}

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline TBasicFixedString<CharTy, N>& TBasicFixedString<CharTy, N>::operator+=(const TBasicFixedString<CharTy, N2>& rhs)
{
	assert(N > m_length + rhs.Length() && "TBasicFixedString buffer overflowed");

	std::memcpy(&m_str[m_length], rhs.CStr(), sizeof(CharTy) * (rhs.Length() + 1));

	m_length += rhs.Length();

	return *this;
}

template<typename CharTy, std::size_t N>
inline TBasicFixedString<CharTy, N>& TBasicFixedString<CharTy, N>::operator+=(const TBasicFixedString& rhs)
{
	assert(N > m_length + rhs.Length() && "TBasicFixedString buffer overflowed");

	std::memcpy(&m_str[m_length], rhs.m_str.data(), sizeof(CharTy) * (rhs.m_length + 1));

	m_length += rhs.m_length;

	return *this;
}

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline bool TBasicFixedString<CharTy, N>::operator==(const TBasicFixedString<CharTy, N2>& rhs) const
{
	return this->Compare(rhs) == 0;
}

template<typename CharTy, std::size_t N>
inline CharTy TBasicFixedString<CharTy, N>::operator[](std::size_t index) const
{
	return m_str[index];
}

template<typename CharTy, std::size_t N>
inline CharTy& TBasicFixedString<CharTy, N>::operator[](std::size_t index)
{
	return m_str[index];
}

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline TBasicFixedString<CharTy, N + N2> TBasicFixedString<CharTy, N>::Extend(const TBasicFixedString<CharTy, N2>& rhs) const
{
	TBasicFixedString<CharTy, N + N2> ret = *this;
	ret += rhs;

	return ret;
}

template<typename CharTy, std::size_t N>
template<std::size_t N2>
inline void TBasicFixedString<CharTy, N>::Assign(const CharTy(&str)[N2])
{
	std::memcpy(m_str.data(), str, sizeof(CharTy) * N2);

	m_length = N2 - 1;
}

template<typename CharTy, std::size_t N>
inline void TBasicFixedString<CharTy, N>::Assign(const CharTy * str, std::size_t length)
{
	std::memcpy(m_str.data(), str, sizeof(CharTy) * (length + 1));

	m_length = length;
}

template<typename CharTy, std::size_t N>
inline void TBasicFixedString<CharTy, N>::Assign(std::size_t length, CharTy ch)
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
inline int32_t TBasicFixedString<CharTy, N>::Compare(const TBasicFixedString<CharTy, N2>& rhs) const
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
inline int32_t TBasicFixedString<CharTy, N>::Find(CharTy ch, std::size_t offset) const
{
	return this->Find(&ch, offset, 1);
}

template<typename CharTy, std::size_t N>
inline int32_t TBasicFixedString<CharTy, N>::Find(const CharTy* ch, std::size_t offset, std::size_t count) const
{
	// TODO: 테스트 필요
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
inline void TBasicFixedString<CharTy, N>::Swap(TBasicFixedString& rhs)
{
	if (rhs != this)
	{
		m_str.swap(rhs.m_str);
		std::swap(m_length, rhs.m_length);
	}
}

template<typename CharTy, std::size_t N>
inline const CharTy* TBasicFixedString<CharTy, N>::CStr() const noexcept
{
	return m_str.data();
}

template<typename CharTy, std::size_t N>
inline std::size_t string::TBasicFixedString<CharTy, N>::Length() const noexcept
{
	return m_length;
}

template<typename CharTy, std::size_t N>
inline constexpr std::size_t tgon::string::TBasicFixedString<CharTy, N>::Capacity() const noexcept
{
	return N;
}

template<typename CharTy, std::size_t N>
inline CharTy& tgon::string::TBasicFixedString<CharTy, N>::At(std::size_t index)
{
	assert(index <= m_length && "TBasicFixedString index out of range");

	return m_str[index];
}

template<typename CharTy, std::size_t N>
inline CharTy TBasicFixedString<CharTy, N>::At(std::size_t index) const
{
	assert(index <= m_length && "TBasicFixedString index out of range");

	return m_str[index];
}

} /* namespace string */
} /* namespace tgon */