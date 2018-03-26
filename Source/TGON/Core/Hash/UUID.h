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

#include "Core/String/FixedString.h"

#ifdef _MSC_VER
#   pragma comment(lib, "Rpcrt4.lib")
#endif

namespace tgon
{

template <typename _CharType, typename _StringTraitsType = StringTraits<_CharType>>
struct BasicUUID :
    private BasicFixedString<_CharType, 37, _StringTraitsType>
{
/* @section Public type */
public:
    using CharType = char;
    using ConstReferenceType = const CharType&;
    using ConstIteratorType = const CharType*;
    using ConstPointerType = const CharType*;
    using ConstReverseIteratorType = std::reverse_iterator<ConstIteratorType>;

/* @section Private constructor */
private:
    constexpr BasicUUID() noexcept;

/* @section Public operator */
public:
    using BasicFixedString::operator=;
    using BasicFixedString::operator[];

/* @section Public method */
public:
    static BasicUUID NewUUID();

    using BasicFixedString::Compare;
    using BasicFixedString::Find;
    using BasicFixedString::RFind;
    using BasicFixedString::At;
    using BasicFixedString::CStr;
    using BasicFixedString::Data;
    using BasicFixedString::Length;
    using BasicFixedString::cbegin;
    using BasicFixedString::crbegin;
};

using UUID = BasicUUID<StringTraits<char>>;

template <typename _CharType, typename _StringTraitsType = StringTraits<_CharType>>
inline BasicUUID<_CharType, _StringTraitsType> BasicUUID<_CharType, _StringTraitsType>::NewUUID()
{
#ifdef _MSC_VER
    ::UUID rawUUID;
    UuidCreate(&rawUUID);

    RPC_CSTR rawUUIDStr;
    UuidToStringA(&rawUUID, &rawUUIDStr);
    
    BasicUUID ret;
    memcpy(ret.m_str, rawUUIDStr, sizeof(decltype(m_str[0])) * std::extent<decltype(m_str)>::value);

    RpcStringFreeA(&rawUUIDStr);

    return ret;
#else
    uuid_t uuid;
    uuid_generate_random(uuid);

    BasicUUID ret;
    uuid_unparse(uuid, ret.m_str);
    return ret;
#endif
}

} /* namespace tgon */