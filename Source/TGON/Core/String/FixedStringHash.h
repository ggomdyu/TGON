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
    BasicFixedStringHash(const _CharType* str);
    BasicFixedStringHash(const _CharType* str, std::size_t strLen) noexcept;

/* @section Public operator */
public:
    using SuperType::operator==;
    using SuperType::operator[];
    
/* @section Public method */
public:
    void Assign(const _CharType* str, std::size_t strLen);
    void Assign(const _CharType* str);
    using SuperType::Compare;
    using SuperType::Find;
    using SuperType::RFind;
    using SuperType::CStr;
    using SuperType::Data;
    const _CharType& At(std::size_t index) const;
    using SuperType::Size;
    using SuperType::Length;
    using SuperType::Capacity;
    ConstIteratorType begin() const noexcept;
    ConstIteratorType end() const noexcept;
    using SuperType::cbegin;
    using SuperType::cend;
    using SuperType::crbegin;
    using SuperType::crend;
    std::size_t GetHashCode() const noexcept;
    
/* @section Private variable */
private:
    size_t m_hashCode;
};

using FixedStringHash8 = BasicFixedStringHash<char, 8>;
using FixedStringHash16 = BasicFixedStringHash<char, 16>;
using FixedStringHash32 = BasicFixedStringHash<char, 32>;
using FixedStringHash64 = BasicFixedStringHash<char, 64>;
using FixedStringHash128 = BasicFixedStringHash<char, 128>;
using FixedStringHash256 = BasicFixedStringHash<char, 256>;
using FixedStringHash512 = BasicFixedStringHash<char, 512>;
using FixedStringHash1024 = BasicFixedStringHash<char, 1024>;

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline BasicFixedStringHash<_CharType, _CharArraySize, _StringTraitsType>::BasicFixedStringHash(const _CharType* str) :
    SuperType(str),
    m_hashCode(X65599Hash(str))
{
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline BasicFixedStringHash<_CharType, _CharArraySize, _StringTraitsType>::BasicFixedStringHash(const _CharType* str, std::size_t strLen) noexcept :
    SuperType(str, strLen),
    m_hashCode(X65599Hash(str))
{
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline void BasicFixedStringHash<_CharType, _CharArraySize, _StringTraitsType>::Assign(const _CharType* str)
{
    new (this) BasicFixedStringHash(str);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline void BasicFixedStringHash<_CharType, _CharArraySize, _StringTraitsType>::Assign(const _CharType* str, std::size_t strLen)
{
    new (this) BasicFixedStringHash(str, strLen);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline const _CharType& BasicFixedStringHash<_CharType, _CharArraySize, _StringTraitsType>::At(std::size_t index) const
{
    return SuperType::At(index);
}
    
template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline std::size_t BasicFixedStringHash<_CharType, _CharArraySize, _StringTraitsType>::GetHashCode() const noexcept
{
    return m_hashCode;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline typename BasicFixedStringHash<_CharType, _CharArraySize, _StringTraitsType>::ConstIteratorType BasicFixedStringHash<_CharType, _CharArraySize, _StringTraitsType>::begin() const noexcept
{
    return this->cbegin();
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline typename BasicFixedStringHash<_CharType, _CharArraySize, _StringTraitsType>::ConstIteratorType BasicFixedStringHash<_CharType, _CharArraySize, _StringTraitsType>::end() const noexcept
{
    return this->cend();
}

} /* namespace tgon */
