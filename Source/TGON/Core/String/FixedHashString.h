/**
 * @file    FixedHashString.h
 * @author  ggomdyu
 * @date    05/30/2018
 */

#pragma once
#include "Core/Hash/Hash.h"

#include "FixedString.h"

namespace tgon
{

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType = StringTraits<_CharType>>
class BasicFixedHashString :
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
    BasicFixedHashString(const _CharType* str);
    BasicFixedHashString(const _CharType* str, std::size_t strLen) noexcept;

/* @section Public operator */
public:
    bool operator==(const BasicFixedHashString& rhs) const noexcept;
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

using FixedHashString8 = BasicFixedHashString<char, 8>;
using FixedHashString16 = BasicFixedHashString<char, 16>;
using FixedHashString32 = BasicFixedHashString<char, 32>;
using FixedHashString64 = BasicFixedHashString<char, 64>;
using FixedHashString128 = BasicFixedHashString<char, 128>;
using FixedHashString256 = BasicFixedHashString<char, 256>;
using FixedHashString512 = BasicFixedHashString<char, 512>;
using FixedHashString1024 = BasicFixedHashString<char, 1024>;

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline BasicFixedHashString<_CharType, _CharArraySize, _StringTraitsType>::BasicFixedHashString(const _CharType* str) :
    SuperType(str),
    m_hashCode(X65599Hash(str))
{
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline BasicFixedHashString<_CharType, _CharArraySize, _StringTraitsType>::BasicFixedHashString(const _CharType* str, std::size_t strLen) noexcept :
    SuperType(str, strLen),
    m_hashCode(X65599Hash(str))
{
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline bool BasicFixedHashString<_CharType, _CharArraySize, _StringTraitsType>::operator==(const BasicFixedHashString& rhs) const noexcept
{
    return m_hashCode == rhs.m_hashCode;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline void BasicFixedHashString<_CharType, _CharArraySize, _StringTraitsType>::Assign(const _CharType* str)
{
    new (this) BasicFixedHashString(str);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline void BasicFixedHashString<_CharType, _CharArraySize, _StringTraitsType>::Assign(const _CharType* str, std::size_t strLen)
{
    new (this) BasicFixedHashString(str, strLen);
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline const _CharType& BasicFixedHashString<_CharType, _CharArraySize, _StringTraitsType>::At(std::size_t index) const
{
    return SuperType::At(index);
}
    
template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline std::size_t BasicFixedHashString<_CharType, _CharArraySize, _StringTraitsType>::GetHashCode() const noexcept
{
    return m_hashCode;
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline typename BasicFixedHashString<_CharType, _CharArraySize, _StringTraitsType>::ConstIteratorType BasicFixedHashString<_CharType, _CharArraySize, _StringTraitsType>::begin() const noexcept
{
    return this->cbegin();
}

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType>
inline typename BasicFixedHashString<_CharType, _CharArraySize, _StringTraitsType>::ConstIteratorType BasicFixedHashString<_CharType, _CharArraySize, _StringTraitsType>::end() const noexcept
{
    return this->cend();
}

} /* namespace tgon */
