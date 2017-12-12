/**
 * @filename    UUID.h
 * @author      ggomdyu
 * @date        10/28/2017
 * @see         https://en.wikipedia.org/wiki/Universally_unique_identifier
 */

#pragma once
#include <cstring>
#ifdef _MSC_VER
#   include <rpc.h>
#else
#   include <uuid/uuid.h>
#endif

#ifdef _MSC_VER
#   pragma comment(lib, "Rpcrt4.lib")
#endif

//#include "Core/String/StringTraits.h"
#include "StringTraits.h"

namespace tgon
{
namespace hash
{

struct UUID
{
/* @section Public type */
public:
    using CharType = char;
    using ReferenceType = CharType&;
    using ConstReferenceType = const CharType&;
    using IteratorType = CharType*;
    using ConstIteratorType = const CharType*;
    using PointerType = CharType*;
    using ConstPointerType = const CharType*;
    using ReverseIteratorType = std::reverse_iterator<IteratorType>;
    using ConstReverseIteratorType = std::reverse_iterator<ConstIteratorType>;

/* section  Private constructor */
private:
    constexpr UUID() noexcept;

/* section  Public method */
public:
    static UUID NewUUID();
    static constexpr UUID Empty();

    int32_t Compare(const CharType* str, std::size_t strLen) const;
    template <std::size_t _CharArraySize2>
    int32_t Compare(const CharType(&str)[_CharArraySize2]) const;
    template<typename _CharPointerType, std::enable_if_t<std::is_pointer<_CharPointerType>::value>* = nullptr>
    int32_t Compare(const _CharPointerType str) const;
    template <std::size_t _CharArraySize2>
    int32_t Compare(const UUID<CharType, _CharArraySize2, _StringTraitsType>& str) const;

    template <std::size_t _CharArraySize2>
    std::size_t Find(const CharType(&str)[_CharArraySize2], std::size_t strOffset = 0) const;
    std::size_t Find(const CharType* str, std::size_t strOffset, std::size_t strLen) const;
    std::size_t Find(const UUID& rhs) const;
    template <std::size_t _CharArraySize2>
    std::size_t Find(const UUID<CharType, _CharArraySize2, _StringTraitsType>& rhs) const;
    std::size_t Find(CharType ch, std::size_t strOffset = 0) const;

    std::size_t RFind(const CharType* str, std::size_t strOffset, std::size_t strLen) const;
    template <std::size_t _CharArraySize2>
    std::size_t RFind(const CharType(&str)[_CharArraySize2], std::size_t strOffset = _StringTraitsType::NPos) const;
    std::size_t RFind(const UUID& rhs) const;
    template <std::size_t _CharArraySize2>
    std::size_t RFind(const UUID<CharType, _CharArraySize2, _StringTraitsType>& rhs) const;
    std::size_t RFind(CharType ch, std::size_t strOffset = _StringTraitsType::NPos) const;

    CharType& At(std::size_t index);
    const CharType& At(std::size_t index) const;

    const CharType* CStr() const noexcept;
    const CharType* Data() const noexcept;

    std::size_t Length() const noexcept;
    constexpr std::size_t Capacity() const noexcept;

    IteratorType begin() noexcept;
    IteratorType end() noexcept;
    ConstIteratorType cbegin() const noexcept;
    ConstIteratorType cend() const noexcept;
    ReverseIteratorType rbegin() noexcept;
    ReverseIteratorType rend() noexcept;
    ConstReverseIteratorType crbegin() const noexcept;
    ConstReverseIteratorType crend() const noexcept;

/* section  Private variable */
private:
    CharType m_uuid[37];
};

constexpr UUID::UUID() noexcept :
    m_uuid{}
{
}

inline UUID UUID::NewUUID()
{
#ifdef _MSC_VER
    ::UUID rawUUID;
    UuidCreate(&rawUUID);

    RPC_CSTR rawUUIDStr;
    UuidToStringA(&rawUUID, &rawUUIDStr);
    
    UUID retUUID;
    memcpy(retUUID.m_uuid, rawUUIDStr, sizeof(decltype(m_uuid[0])) * std::extent<decltype(m_uuid)>::value);
    RpcStringFreeA(&rawUUIDStr);

    return retUUID;
#else
    uuid_t uuid;
    uuid_generate_random(uuid);

    UUID ret;
    uuid_unparse(uuid, ret.m_uuid);
    return ret;
#endif
}

constexpr UUID UUID::Empty()
{
    return UUID();
}

} /* namespace hash */
} /* namespace tgon */
