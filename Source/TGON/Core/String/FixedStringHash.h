/**
 * @filename    StringViewHash.h
 * @author      ggomdyu
 * @date        05/30/2018
 */

#pragma once
#include "Core/Hash/Hash.h"

#include "FixedString.h"

namespace tgon
{

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType = StringTraits<_CharType>>
class BasicFixedStringHash :
    private BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>
{
/* @section Private type */
private:
    using SuperType = BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>;
    
/* @section Public type */
public:
    using CharType = typename SuperType::CharType;
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
    constexpr BasicFixedStringHash(const _CharType(&str)[_CharArraySize]) noexcept;
    constexpr BasicFixedStringHash(const _CharType* str, std::size_t strLen) noexcept;

/* @section Public operator */
public:
    using SuperType::operator==;
    using SuperType::operator[];
    
/* @section Public method */
public:
    using SuperType::Compare;
    using SuperType::Find;
    using SuperType::RFind;
    using SuperType::Data;
    using SuperType::At;
    using SuperType::Length;
    using SuperType::begin;
    using SuperType::end;
    using SuperType::cbegin;
    using SuperType::cend;
    using SuperType::rbegin;
    using SuperType::rend;
    using SuperType::crbegin;
    using SuperType::crend;
    
    constexpr std::size_t GetHashCode() const noexcept;
    
/* @section Private variable */
private:
    size_t m_hashCode;
};

using StringViewHash = BasicFixedStringHash<char>;
using WStringViewHash = BasicFixedStringHash<wchar_t>;

template <typename _CharType, typename _StringTraitsType>
template <std::size_t _CharArraySize>
constexpr BasicFixedStringHash<_CharType, _StringTraitsType>::BasicFixedStringHash(const _CharType(&str)[_CharArraySize]) noexcept :
    SuperType(str, _CharArraySize - 1),
    m_hashCode(X65599Hash(str))
{
}

template <typename _CharType, typename _StringTraitsType>
constexpr BasicFixedStringHash<_CharType, _StringTraitsType>::BasicFixedStringHash(const _CharType* str, std::size_t strLen) noexcept :
    m_str(str),
    m_strLen(strLen),
    m_hashCode(X65599Hash(str))
{
}
    
template <typename _CharType, typename _StringTraitsType>
constexpr std::size_t BasicFixedStringHash<_CharType, _StringTraitsType>::GetHashCode() const noexcept
{
    return m_hashCode;
}

} /* namespace tgon */
