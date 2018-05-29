/**
 * @filename    StringView.h
 * @author      ggomdyu
 * @date        10/27/2017
 */

#pragma once
#include "StringTraits.h"

namespace tgon
{

template <typename _CharType, typename _StringTraitsType = StringTraits<_CharType>>
class BasicStringView :
    private _StringTraitsType
{
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
    template <std::size_t _CharArraySize>
    constexpr BasicStringView(const _CharType(&str)[_CharArraySize]) noexcept;
    constexpr BasicStringView(const _CharType* str, std::size_t strLen) noexcept;

/* @section Public operator */
public:
    bool operator==(const BasicStringView& rhs) const;
    constexpr const _CharType operator[](std::size_t index) const;
    constexpr _CharType& operator[](std::size_t index);
    
/* @section Public method */
public:
    template <std::size_t _CharArraySize2>
    int32_t Compare(const _CharType(&str)[_CharArraySize2]) const;
    int32_t Compare(const _CharType* str, std::size_t strLen) const;
    int32_t Compare(const BasicStringView& strView) const;
    std::size_t Find(const BasicStringView& rhs) const;
    std::size_t Find(_CharType ch, std::size_t strOffset = 0) const;
    template <std::size_t _CharArraySize2>
    std::size_t Find(const _CharType(&str)[_CharArraySize2], std::size_t strOffset = 0) const;
    std::size_t Find(const _CharType* str, std::size_t strOffset, std::size_t strLen) const;
    std::size_t RFind(const BasicStringView& rhs) const;
    std::size_t RFind(_CharType ch, std::size_t strOffset = _StringTraitsType::NPos) const;
    template <std::size_t _CharArraySize2>
    std::size_t RFind(const _CharType(&str)[_CharArraySize2], std::size_t strOffset = _StringTraitsType::NPos) const;
    std::size_t RFind(const _CharType* str, std::size_t strOffset, std::size_t strLen) const;
    constexpr const _CharType* Data() const noexcept;
    constexpr _CharType& At(std::size_t index);
    constexpr const _CharType At(std::size_t index) const;
    constexpr std::size_t Length() const noexcept;
    constexpr IteratorType begin() noexcept;
    constexpr IteratorType end() noexcept;
    constexpr ConstIteratorType cbegin() const noexcept;
    constexpr ConstIteratorType cend() const noexcept;
    constexpr ReverseIteratorType rbegin() noexcept;
    constexpr ReverseIteratorType rend() noexcept;
    constexpr ConstReverseIteratorType crbegin() const noexcept;
    constexpr ConstReverseIteratorType crend() const noexcept;
    
/* @section Private variable */
private:
    const _CharType* m_str;
    std::size_t m_strLen;
};

using StringView = BasicStringView<char>;
using WStringView = BasicStringView<wchar_t>;

template <typename _CharType, typename _StringTraitsType>
template <std::size_t _CharArraySize>
constexpr BasicStringView<_CharType, _StringTraitsType>::BasicStringView(const _CharType(&str)[_CharArraySize]) noexcept :
    m_str(str),
    m_strLen(_CharArraySize - 1)
{
}

template <typename _CharType, typename _StringTraitsType>
constexpr BasicStringView<_CharType, _StringTraitsType>::BasicStringView(const _CharType* str, std::size_t strLen) noexcept :
    m_str(str),
    m_strLen(strLen)
{
}

template <typename _CharType, typename _StringTraitsType>
inline bool BasicStringView<_CharType, _StringTraitsType>::operator==(const BasicStringView& rhs) const
{
    return _StringTraitsType::Compare(m_str, m_strLen, rhs.m_str, rhs.m_strLen) == 0;
}

template <typename _CharType, typename _StringTraitsType>
constexpr const _CharType BasicStringView<_CharType, _StringTraitsType>::operator[](std::size_t index) const
{
    return m_str[index];
}

template <typename _CharType, typename _StringTraitsType>
constexpr _CharType& BasicStringView<_CharType, _StringTraitsType>::operator[](std::size_t index)
{
    return m_str[index];
}

template <typename _CharType, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline int32_t BasicStringView<_CharType, _StringTraitsType>::Compare(const _CharType(&str)[_CharArraySize2]) const
{
    return _StringTraitsType::Compare(m_str, m_strLen, str, _CharArraySize2 - 1);
}

template <typename _CharType, typename _StringTraitsType>
inline int32_t BasicStringView<_CharType, _StringTraitsType>::Compare(const _CharType* str, std::size_t strLen) const
{
    return _StringTraitsType::Compare(m_str, m_strLen, str, strLen);
}

template <typename _CharType, typename _StringTraitsType>
inline int32_t BasicStringView<_CharType, _StringTraitsType>::Compare(const BasicStringView& strView) const
{
    return _StringTraitsType::Compare(m_str, m_strLen, strView.m_str, strView.m_strLen);
}

template <typename _CharType, typename _StringTraitsType>
inline std::size_t BasicStringView<_CharType, _StringTraitsType>::Find(const BasicStringView& rhs) const
{
    return _StringTraitsType::Find(m_str, m_strLen, 0, rhs.m_str, rhs.m_strLen);
}

template <typename _CharType, typename _StringTraitsType>
inline std::size_t BasicStringView<_CharType, _StringTraitsType>::Find(_CharType ch, std::size_t strOffset) const
{
    return _StringTraitsType::Find(m_str, m_strLen, strOffset, &ch, 1);
}

template <typename _CharType, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline std::size_t BasicStringView<_CharType, _StringTraitsType>::Find(const _CharType(&str)[_CharArraySize2], std::size_t strOffset) const
{
    return _StringTraitsType::Find(m_str, m_strLen, strOffset, str, _CharArraySize2 - 1);
}

template <typename _CharType, typename _StringTraitsType>
inline std::size_t BasicStringView<_CharType, _StringTraitsType>::Find(const _CharType* str, std::size_t strOffset, std::size_t strLen) const
{
    return _StringTraitsType::Find(m_str, m_strLen, strOffset, str, strLen);
}

template <typename _CharType, typename _StringTraitsType>
inline std::size_t BasicStringView<_CharType, _StringTraitsType>::RFind(const BasicStringView& rhs) const
{
    return _StringTraitsType::RFind(m_str, m_strLen, 0, rhs.m_str, rhs.m_strLen);
}

template<typename _CharType, typename _StringTraitsType>
inline std::size_t BasicStringView<_CharType, _StringTraitsType>::RFind(_CharType ch, std::size_t strOffset) const
{
    return _StringTraitsType::RFind(m_str, m_strLen, strOffset, &ch, 1);
}

template <typename _CharType, typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline std::size_t BasicStringView<_CharType, _StringTraitsType>::RFind(const _CharType(&str)[_CharArraySize2], std::size_t strOffset) const
{
    return _StringTraitsType::RFind(m_str, m_strLen, strOffset, str, _CharArraySize2 - 1);
}

template <typename _CharType, typename _StringTraitsType>
inline std::size_t BasicStringView<_CharType, _StringTraitsType>::RFind(const _CharType* str, std::size_t strOffset, std::size_t strLen) const
{
    return _StringTraitsType::RFind(m_str, m_strLen, strOffset, str, strLen);
}

template <typename _CharType, typename _StringTraitsType>
constexpr std::size_t BasicStringView<_CharType, _StringTraitsType>::Length() const noexcept
{
    return m_strLen;
}

template <typename _CharType, typename _StringTraitsType>
constexpr typename BasicStringView<_CharType, _StringTraitsType>::IteratorType BasicStringView<_CharType, _StringTraitsType>::begin() noexcept
{
    return m_str;
}

template <typename _CharType, typename _StringTraitsType>
constexpr typename BasicStringView<_CharType, _StringTraitsType>::IteratorType BasicStringView<_CharType, _StringTraitsType>::end() noexcept
{
    return m_str + m_strLen;
}

template <typename _CharType, typename _StringTraitsType>
constexpr typename BasicStringView<_CharType, _StringTraitsType>::ConstIteratorType BasicStringView<_CharType, _StringTraitsType>::cbegin() const noexcept
{
    return m_str;
}

template <typename _CharType, typename _StringTraitsType>
constexpr typename BasicStringView<_CharType, _StringTraitsType>::ConstIteratorType BasicStringView<_CharType, _StringTraitsType>::cend() const noexcept
{
    return m_str + m_strLen;
}

template <typename _CharType, typename _StringTraitsType>
constexpr typename BasicStringView<_CharType, _StringTraitsType>::ReverseIteratorType BasicStringView<_CharType, _StringTraitsType>::rbegin() noexcept
{
    return ReverseIteratorType(this->end());
}

template <typename _CharType, typename _StringTraitsType>
constexpr typename BasicStringView<_CharType, _StringTraitsType>::ReverseIteratorType BasicStringView<_CharType, _StringTraitsType>::rend() noexcept
{
    return ReverseIteratorType(this->begin());
}

template <typename _CharType, typename _StringTraitsType>
constexpr typename BasicStringView<_CharType, _StringTraitsType>::ConstReverseIteratorType BasicStringView<_CharType, _StringTraitsType>::crbegin() const noexcept
{
    return ReverseIteratorType(this->cend());
}

template <typename _CharType, typename _StringTraitsType>
constexpr typename BasicStringView<_CharType, _StringTraitsType>::ConstReverseIteratorType BasicStringView<_CharType, _StringTraitsType>::crend() const noexcept
{
    return ReverseIteratorType(this->cbegin());
}

template <typename _CharType, typename _StringTraitsType>
constexpr const _CharType* BasicStringView<_CharType, _StringTraitsType>::Data() const noexcept
{
    return m_str;
}

template <typename _CharType, typename _StringTraitsType>
constexpr _CharType& BasicStringView<_CharType, _StringTraitsType>::At(std::size_t index)
{
    return _StringTraitsType::At(m_str, index);
}

template <typename _CharType, typename _StringTraitsType>
constexpr const _CharType BasicStringView<_CharType, _StringTraitsType>::At(std::size_t index) const
{
    return _StringTraitsType::At(m_str, index);
}

} /* namespace tgon */
