/**
 * @filename    UUID.h
 * @author      ggomdyu
 * @date        10/28/2017
 * @see         https://en.wikipedia.org/wiki/Universally_unique_identifier
 */

#pragma once
#include "Core/String/StringTraits.h"

#include <cstring>
#ifdef _MSC_VER
#   include <rpc.h>
#else
#   include <uuid/uuid.h>
#endif

#ifdef _MSC_VER
#   pragma comment(lib, "Rpcrt4.lib")
#endif

namespace tgon
{
namespace hash
{

template <typename _StringTraitsType = string::StringTraits<char>>
struct BasicUUID :
    private _StringTraitsType
{
/* @section Public type */
public:
    using CharType = char;
    using ConstReferenceType = const CharType&;
    using ConstIteratorType = const CharType*;
    using ConstPointerType = const CharType*;
    using ConstReverseIteratorType = std::reverse_iterator<ConstIteratorType>;

/* section  Private constructor */
private:
    constexpr BasicUUID() noexcept;

/* @section Public operator */
public:
    template <std::size_t _CharArraySize2>
    bool operator==(const CharType(&rhs)[_CharArraySize2]) const;
    template <typename _CharPointerType, std::enable_if_t<std::is_pointer<_CharPointerType>::value>* = nullptr>
    bool operator==(const _CharPointerType rhs) const;

    const CharType& operator[](std::size_t index) const;

/* section  Public method */
public:
    static BasicUUID NewUUID();

    int32_t Compare(const CharType* str, std::size_t strLen) const;
    template <std::size_t _CharArraySize2>
    int32_t Compare(const CharType(&str)[_CharArraySize2]) const;
    template <typename _CharPointerType, std::enable_if_t<std::is_pointer<_CharPointerType>::value>* = nullptr>
    int32_t Compare(const _CharPointerType str) const;
    
    template <std::size_t _CharArraySize2>
    std::size_t Find(const CharType(&str)[_CharArraySize2], std::size_t strOffset = 0) const;
    std::size_t Find(const CharType* str, std::size_t strOffset, std::size_t strLen) const;
    std::size_t Find(const BasicUUID& rhs) const;
    std::size_t Find(CharType ch, std::size_t strOffset = 0) const;
    
    std::size_t RFind(const CharType* str, std::size_t strOffset, std::size_t strLen) const;
    template <std::size_t _CharArraySize2>
    std::size_t RFind(const CharType(&str)[_CharArraySize2], std::size_t strOffset = _StringTraitsType::NPos) const;
    std::size_t RFind(const BasicUUID& rhs) const;
    std::size_t RFind(CharType ch, std::size_t strOffset = _StringTraitsType::NPos) const;
    
    const CharType& At(std::size_t index) const;
    
    const CharType* CStr() const noexcept;
    const CharType* Data() const noexcept;
    
    constexpr std::size_t Length() const noexcept;
    
    ConstIteratorType cbegin() const noexcept;
    ConstIteratorType cend() const noexcept;
    ConstReverseIteratorType crbegin() const noexcept;
    ConstReverseIteratorType crend() const noexcept;

/* section  Private variable */
private:
    CharType m_uuid[37];
};

using UUID = BasicUUID<string::StringTraits<char>>;

template <typename _StringTraitsType>
constexpr BasicUUID<_StringTraitsType>::BasicUUID() noexcept :
    m_uuid{}
{
}

template <typename _StringTraitsType>
inline BasicUUID<_StringTraitsType> BasicUUID<_StringTraitsType>::NewUUID()
{
#ifdef _MSC_VER
    ::UUID rawUUID;
    UuidCreate(&rawUUID);

    RPC_CSTR rawUUIDStr;
    UuidToStringA(&rawUUID, &rawUUIDStr);
    
    BasicUUID ret;
    memcpy(ret.m_uuid, rawUUIDStr, sizeof(decltype(m_uuid[0])) * std::extent<decltype(m_uuid)>::value);

    RpcStringFreeA(&rawUUIDStr);

    return ret;
#else
    uuid_t uuid;
    uuid_generate_random(uuid);

    BasicUUID ret;
    uuid_unparse(uuid, ret.m_uuid);
    return ret;
#endif
}

template <typename _StringTraitsType>
template <typename _CharPointerType, std::enable_if_t<std::is_pointer<_CharPointerType>::value>*>
inline bool BasicUUID<_StringTraitsType>::operator==(const _CharPointerType rhs) const
{
    return _StringTraitsType::Compare(m_uuid, std::extent<decltype(m_uuid)>::value, rhs, _StringTraitsType::Length(rhs)) == 0;
}

template <typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline bool BasicUUID<_StringTraitsType>::operator==(const CharType(&rhs)[_CharArraySize2]) const
{
    return _StringTraitsType::Compare(m_uuid, std::extent<decltype(m_uuid)>::value, rhs, _CharArraySize2 - 1) == 0;
}

template <typename _StringTraitsType>
inline const typename BasicUUID<_StringTraitsType>::CharType& BasicUUID<_StringTraitsType>::operator[](std::size_t index) const
{
	return _StringTraitsType::At(m_uuid, std::extent<decltype(m_uuid)>::value, index);
}

template <typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline int32_t BasicUUID<_StringTraitsType>::Compare(const CharType(&str)[_CharArraySize2]) const
{
    return _StringTraitsType::Compare(m_uuid, std::extent<decltype(m_uuid)>::value, str, _CharArraySize2 - 1);
}

template <typename _StringTraitsType>
inline int32_t BasicUUID<_StringTraitsType>::Compare(const CharType* str, std::size_t strLen) const
{
    return _StringTraitsType::Compare(m_uuid, std::extent<decltype(m_uuid)>::value, str, strLen);
}

template <typename _StringTraitsType>
template <typename _CharPointerType, std::enable_if_t<std::is_pointer<_CharPointerType>::value>*>
inline int32_t BasicUUID<_StringTraitsType>::Compare(const _CharPointerType str) const
{
    return _StringTraitsType::Compare(m_uuid, std::extent<decltype(m_uuid)>::value, str, _StringTraitsType::Length(str));
}

template <typename _StringTraitsType>
inline std::size_t BasicUUID<_StringTraitsType>::Find(const BasicUUID& rhs) const
{
    return _StringTraitsType::Find(m_uuid, std::extent<decltype(m_uuid)>::value, 0, rhs.CStr(), rhs.Length());
}

template <typename _StringTraitsType>
inline std::size_t BasicUUID<_StringTraitsType>::Find(CharType ch, std::size_t strOffset) const
{
	return _StringTraitsType::Find(m_uuid, std::extent<decltype(m_uuid)>::value, strOffset, &ch, 1);
}

template <typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline std::size_t BasicUUID<_StringTraitsType>::Find(const CharType(&str)[_CharArraySize2], std::size_t strOffset) const
{
    return _StringTraitsType::Find(m_uuid, std::extent<decltype(m_uuid)>::value, strOffset, str, _CharArraySize2 - 1);
}

template <typename _StringTraitsType>
inline std::size_t BasicUUID<_StringTraitsType>::Find(const CharType* str, std::size_t strOffset, std::size_t strLen) const
{
    return _StringTraitsType::Find(m_uuid, std::extent<decltype(m_uuid)>::value, strOffset, str, strLen);
}

template <typename _StringTraitsType>
inline std::size_t BasicUUID<_StringTraitsType>::RFind(const BasicUUID& rhs) const
{
    return _StringTraitsType::RFind(m_uuid, std::extent<decltype(m_uuid)>::value, 0, rhs.CStr(), rhs.Length());
}

template <typename _StringTraitsType>
inline std::size_t BasicUUID<_StringTraitsType>::RFind(CharType ch, std::size_t strOffset) const
{
    return _StringTraitsType::RFind(m_uuid, std::extent<decltype(m_uuid)>::value, strOffset, &ch, 1);
}

template <typename _StringTraitsType>
template <std::size_t _CharArraySize2>
inline std::size_t BasicUUID<_StringTraitsType>::RFind(const CharType(&str)[_CharArraySize2], std::size_t strOffset) const
{
    return _StringTraitsType::RFind(m_uuid, std::extent<decltype(m_uuid)>::value, strOffset, str, _CharArraySize2 - 1);
}

template <typename _StringTraitsType>
inline std::size_t BasicUUID<_StringTraitsType>::RFind(const CharType* str, std::size_t strOffset, std::size_t strLen) const
{
    return _StringTraitsType::RFind(m_uuid, std::extent<decltype(m_uuid)>::value, strOffset, str, strLen);
}

template <typename _StringTraitsType>
inline const typename BasicUUID<_StringTraitsType>::CharType* BasicUUID<_StringTraitsType>::CStr() const noexcept
{
    return m_uuid;
}

template <typename _StringTraitsType>
inline const typename BasicUUID<_StringTraitsType>::CharType* BasicUUID<_StringTraitsType>::Data() const noexcept
{
    return m_uuid;
}

template <typename _StringTraitsType>
constexpr std::size_t BasicUUID<_StringTraitsType>::Length() const noexcept
{
    return std::extent<decltype(m_uuid)>::value;
}

template <typename _StringTraitsType>
inline typename BasicUUID<_StringTraitsType>::ConstIteratorType BasicUUID<_StringTraitsType>::cbegin() const noexcept
{
    return m_uuid;
}

template <typename _StringTraitsType>
inline typename BasicUUID<_StringTraitsType>::ConstIteratorType BasicUUID<_StringTraitsType>::cend() const noexcept
{
    return m_uuid + std::extent<decltype(m_uuid)>::value;
}

template <typename _StringTraitsType>
inline typename BasicUUID<_StringTraitsType>::ConstReverseIteratorType BasicUUID<_StringTraitsType>::crbegin() const noexcept
{
    return ConstReverseIteratorType(m_uuid + std::extent<decltype(m_uuid)>::value);
}

template <typename _StringTraitsType>
inline typename BasicUUID<_StringTraitsType>::ConstReverseIteratorType BasicUUID<_StringTraitsType>::crend() const noexcept
{
    return ConstReverseIteratorType(m_uuid);
}

template <typename _StringTraitsType>
inline const typename BasicUUID<_StringTraitsType>::CharType& BasicUUID<_StringTraitsType>::At(std::size_t index) const
{
    return _StringTraitsType::At(m_uuid, std::extent<decltype(m_uuid)>::value, index);
}

} /* namespace hash */
} /* namespace tgon */
