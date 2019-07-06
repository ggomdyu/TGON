/**
 * @file    UUID.h
 * @author  ggomdyu
 * @date    10/28/2017
 * @see     https://en.wikipedia.org/wiki/Universally_unique_identifier
 */

#pragma once
#include <cstring>
#ifdef _MSC_VER
#   include <rpc.h>
#else
#   include <uuid/uuid.h>
#endif

#include "FixedString.h"

#ifdef _MSC_VER
#   pragma comment(lib, "Rpcrt4.lib")
#endif

namespace tgon
{

template <typename _CharType, typename _StringTraitsType = BasicStringTraits<_CharType>>
struct BasicUUID :
    private BasicFixedString<_CharType, 37, _StringTraitsType>
{
/**@section Type */
private:
    using SuperType = BasicFixedString<_CharType, 37, _StringTraitsType>;

public:
    using CharType = _CharType;
    using ConstReferenceType = const CharType&;
    using ConstIteratorType = const CharType*;
    using ConstPointerType = const CharType*;
    using ConstReverseIteratorType = std::reverse_iterator<ConstIteratorType>;
    
/**@section Constructor */
private:
    using SuperType::SuperType;

/**@section Operator */
public:
    using SuperType::operator=;
    const _CharType operator[](size_t index) const;

/**@section Method */
public:
    static BasicUUID NewUUID();
    const _CharType At(size_t index) const;
    const Range<const _CharType> Range() const noexcept;
    using SuperType::Compare;
    using SuperType::Find;
    using SuperType::RFind;
    using SuperType::CStr;
    using SuperType::Data;
    using SuperType::Length;
    using SuperType::Capacity;
};

using UUID = BasicUUID<char, BasicStringTraits<char>>;

template <typename _CharType, typename _StringTraitsType>
inline BasicUUID<_CharType, _StringTraitsType> BasicUUID<_CharType, _StringTraitsType>::NewUUID()
{
#ifdef _MSC_VER
    ::UUID rawUUID;
    UuidCreate(&rawUUID);

    RPC_CSTR rawUUIDStr;
    UuidToStringA(&rawUUID, &rawUUIDStr);
    
    BasicUUID ret({reinterpret_cast<const char*>(rawUUIDStr), 36});
    RpcStringFreeA(&rawUUIDStr);

    return ret;
#else
    uuid_t uuid;
    uuid_generate_random(uuid);

    char rawUUIDStr[37] {};
    uuid_unparse(uuid, rawUUIDStr);
    BasicUUID ret({rawUUIDStr, 36});
    
    return ret;
#endif
}
   
template <typename _CharType, typename _StringTraitsType>
inline const _CharType BasicUUID<_CharType, _StringTraitsType>::operator[](size_t index) const
{
    return SuperType::operator[](index);
}
    
template <typename _CharType, typename _StringTraitsType>
inline const _CharType BasicUUID<_CharType, _StringTraitsType>::At(size_t index) const
{
    return SuperType::At(index);
}
    
template <typename _CharType, typename _StringTraitsType>
inline const Range<const _CharType> BasicUUID<_CharType, _StringTraitsType>::Range() const noexcept
{
    return SuperType::Range();
}
    
} /* namespace tgon */
