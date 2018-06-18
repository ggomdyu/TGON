/**
 * @file    StringViewHash.h
 * @author  ggomdyu
 * @date    05/30/2018
 */

#pragma once
#include "Core/Hash/Hash.h"

#include "StringView.h"

namespace tgon
{

template <typename _CharType, typename _StringTraitsType = StringTraits<_CharType>>
class BasicStringViewHash :
    private BasicStringView<_CharType, _StringTraitsType>
{
/* @section Private type */
private:
    using SuperType = BasicStringView<_CharType, _StringTraitsType>;
    
/* @section Public type */
public:
    using StringTraitsType = typename SuperType::StringTraitsType;
    using SizeType = typename SuperType::SizeType;
    using ValueType = typename SuperType::ValueType;
    using ReferenceType = typename SuperType::ReferenceType;
    using ConstReferenceType = typename SuperType::ConstReferenceType;
    using IteratorType = typename SuperType::IteratorType;
    using ConstIteratorType = typename SuperType::ConstIteratorType;
    using PointerType = typename SuperType::PointerType;
    using ConstPointerType = typename SuperType::ConstPointerType;
    using ReverseIteratorType = typename SuperType::ReverseIteratorType;
    using ConstReverseIteratorType = typename SuperType::ConstReverseIteratorType;

/* @section Public constructor */
public:
    template <std::size_t _CharArraySize>
    constexpr BasicStringViewHash(const _CharType(&str)[_CharArraySize]) noexcept;
    constexpr BasicStringViewHash(const _CharType* str, std::size_t strLen) noexcept;

/* @section Public operator */
public:
    using SuperType::operator==;
    constexpr const _CharType operator[](std::size_t index) const;
    
/* @section Public method */
public:
    using SuperType::Assign;
    using SuperType::Compare;
    using SuperType::Find;
    using SuperType::RFind;
    using SuperType::Data;
    const _CharType& At(std::size_t index) const;
    using SuperType::Length;
    using SuperType::begin;
    using SuperType::end;
    using SuperType::cbegin;
    using SuperType::cend;
    using SuperType::crbegin;
    using SuperType::crend;
    constexpr std::size_t GetHashCode() const noexcept;
    
/* @section Private variable */
private:
    const _CharType* m_str;
    std::size_t m_strLen;
    size_t m_hashCode;
};

using StringViewHash = BasicStringViewHash<char>;
using WStringViewHash = BasicStringViewHash<wchar_t>;

template <typename _CharType, typename _StringTraitsType>
template <std::size_t _CharArraySize>
constexpr BasicStringViewHash<_CharType, _StringTraitsType>::BasicStringViewHash(const _CharType(&str)[_CharArraySize]) noexcept :
    BasicStringViewHash(str, _CharArraySize - 1)
{
}

template <typename _CharType, typename _StringTraitsType>
constexpr BasicStringViewHash<_CharType, _StringTraitsType>::BasicStringViewHash(const _CharType* str, std::size_t strLen) noexcept :
    SuperType(str, strLen),
    m_hashCode(X65599Hash(str))
{
}

template <typename _CharType, typename _StringTraitsType>
constexpr const _CharType BasicStringViewHash<_CharType, _StringTraitsType>::operator[](std::size_t index) const
{
    return SuperType::operator[](index);
}

template <typename _CharType, typename _StringTraitsType>
inline const _CharType& tgon::BasicStringViewHash<_CharType, _StringTraitsType>::At(std::size_t index) const
{
    return SuperType::At(index);
}
    
template <typename _CharType, typename _StringTraitsType>
constexpr std::size_t BasicStringViewHash<_CharType, _StringTraitsType>::GetHashCode() const noexcept
{
    return m_hashCode;
}

} /* namespace tgon */
