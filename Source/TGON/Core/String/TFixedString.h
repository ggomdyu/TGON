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
    using SizeTy = decltype(N);

/**
 * @section Ctor/Dtor
 */
public:
    constexpr TBasicFixedString() noexcept = default;
    
    template <SizeTy N2>
    TBasicFixedString(const CharTy(&str)[N2])
    {
        this->Assign(str);
    }
    TBasicFixedString(const CharTy* str, SizeTy length)
    {
        this->Assign(str, length);
    }
    TBasicFixedString(SizeTy length, CharTy ch)
    {
        this->Assign(length, ch);
    }
    
    template <SizeTy N2>
    TBasicFixedString(const TBasicFixedString<CharTy, N2>& rhs)
    {
        assert(N > rhs.Length() && "TBasicFixedString buffer overflowed");

        this->Assign(rhs.CStr(), rhs.Length());
    }

/**
 * @section Operator
 */
public:
    template <SizeTy N2>
    TBasicFixedString& operator=(const TBasicFixedString<CharTy, N2>& rhs)
    {
        assert(N > rhs.Length() && "TBasicFixedString buffer overflowed");

        this->Assign(rhs.CStr(), rhs.Length());

        return *this;
    }
    TBasicFixedString& operator=(const TBasicFixedString& rhs) = default;

    template <SizeTy N2>
    TBasicFixedString operator+(const TBasicFixedString<CharTy, N2>& rhs) const
    {
        assert(N > m_length + rhs.Length() && "TBasicFixedString buffer overflowed");

        TBasicFixedString<CharTy, N> ret = *this;
        ret += rhs;

        return ret;
    }
    TBasicFixedString operator+(const TBasicFixedString& rhs) const
    {
        assert(N > m_length + rhs.Length() && "TBasicFixedString buffer overflowed");

        TBasicFixedString<CharTy, N> ret = *this;
        ret += rhs;

        return ret;
    }
    TBasicFixedString operator+(CharTy ch) const
    {
        m_str[m_length] = ch;
        m_str[++m_length] = static_cast<CharTy>(0);

        return *this;
    }

    template <SizeTy N2>
    TBasicFixedString& operator+=(const TBasicFixedString<CharTy, N2>& rhs)
    {
        assert(N > m_length + rhs.Length() && "TBasicFixedString buffer overflowed");

        std::memcpy(&m_str[m_length], rhs.CStr(), sizeof(CharTy) * (rhs.Length() + 1));

        m_length += rhs.Length();

        return *this;
    }
    TBasicFixedString& operator+=(const TBasicFixedString& rhs)
    {
        assert(N > m_length + rhs.Length() && "TBasicFixedString buffer overflowed");

        std::memcpy(&m_str[m_length], rhs.m_str.data(), sizeof(CharTy) * (rhs.m_length + 1));

        m_length += rhs.m_length;

        return *this;
    }
    TBasicFixedString& operator+=(CharTy ch);

    template <SizeTy N2>
    bool operator==(const TBasicFixedString<CharTy, N2>& rhs) const
    {
        return this->Compare(rhs) == 0;
    }

    CharTy operator[](int index) const
    {
        return m_str[index]
    }
    CharTy& operator[](int index)
    {
        return m_str[index];
    }

/**
 * @section Public method
 */
public:
    template <SizeTy N2>
    TBasicFixedString<CharTy, N + N2> Extend(const TBasicFixedString<CharTy, N2>& rhs) const
    {
        TBasicFixedString<CharTy, N + N2> ret = *this;
        ret += rhs;

        return ret;
    }

    template <SizeTy N2>
    void Assign(const CharTy(&str)[N2])
    {
        std::memcpy(m_str.data(), str, sizeof(CharTy) * N2);

        m_length = N2 - 1;
    }
    void Assign(const CharTy* str, SizeTy length)
    {
        std::memcpy(m_str.data(), str, sizeof(CharTy) * (length + 1));

        m_length = length;
    }
    void Assign(SizeTy length, CharTy ch)
    {
        int i = 0;
        while (i < length)
        {
            m_str[i++] = ch;
        }

        m_str[i] = static_cast<CharTy>(0);
        m_length = length;
    }

    template <SizeTy N2>
    int Compare(const TBasicFixedString<CharTy, N2>& rhs) const
    {
        SizeTy minSize = m_length < rhs.Length() ? m_length : rhs.Length();

        int ans = TraitsTy::compare(m_str.data(), rhs.CStr(), minSize);
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

    int Find(CharTy ch, SizeTy offset = 0) const
    {
        return this->Find(&ch, offset, 1);
    }
    int Find(const CharTy* ch, SizeTy offset, SizeTy count) const
    {
        // TODO: 테스트 필요
        for (int i = offset;; ++i)
        {
            int ans = TraitsTy::compare(&m_str.data()[offset], ch, count);
            if (ans == 0)
            {
                return i;
            }
        }

        return NPos;
    }
    
    void Swap(TBasicFixedString& rhs)
    {
        using std::swap;

        if (rhs != this)
        {
            m_str.swap(rhs.m_str);

            swap(m_length, rhs.m_length);
        }
    }
    
    const CharTy* CStr() const noexcept
    {
        return m_str.data();
    }
    
    SizeTy Length() const noexcept
    {
        return m_length;
    }
    constexpr SizeTy Capacity() const noexcept
    {
        return N;
    }
    
    CharTy& At(SizeTy index)
    {
        assert(index <= m_length && "TBasicFixedString index out of range");

        return m_str[index];
    }
    CharTy At(SizeTy index) const
    {
        assert(index <= m_length && "TBasicFixedString index out of range");

        return m_str[index];
    }

/**
 * @section Public variable
 */
public:
    static const auto NPos = (SizeTy)(-1);

/**
 * @section Private variable
 */
private:
    SizeTy m_length;
    std::array<CharTy, N> m_str;
};

using TFixedString = TBasicFixedString<char, 32>;
using TFixedWString = TBasicFixedString<wchar_t, 32>;

} /* namespace string */
} /* namespace tgon */