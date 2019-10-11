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

struct UUID :
    private BasicFixedString<char, 37>
{
/**@section Type */
private:
    using SuperType = BasicFixedString<char, 37>;

public:
    using ValueType = char;
    using ConstReferenceType = const char&;
    using ConstIteratorType = const char*;
    using ConstPointerType = const char*;
    using ConstReverseIteratorType = std::reverse_iterator<ConstIteratorType>;
    
/**@section Constructor */
private:
    using SuperType::SuperType;

/**@section Operator */
public:
    using SuperType::operator=;
    using SuperType::operator!=;
    using SuperType::operator==;
    using SuperType::operator std::basic_string<char>;
    using SuperType::operator std::basic_string_view<char>;
    const char operator[](int32_t index) const;
    
/**@section Method */
public:
    static UUID NewUUID();
    ConstIteratorType Begin() const noexcept;
    ConstIteratorType End() const noexcept;
    using SuperType::CompareTo;
    using SuperType::IndexOf;
    using SuperType::IndexOfAny;
    using SuperType::LastIndexOf;
    using SuperType::LastIndexOfAny;
    using SuperType::Data;
    using SuperType::Length;
    using SuperType::Capacity;
    using SuperType::CBegin;
    using SuperType::CEnd;
};

inline UUID UUID::NewUUID()
{
#ifdef _MSC_VER
    ::UUID rawUUID;
    UuidCreate(&rawUUID);

    RPC_CSTR rawUUIDStr;
    UuidToStringA(&rawUUID, &rawUUIDStr);

    UUID ret(reinterpret_cast<char*>(rawUUIDStr), 36);
    RpcStringFreeA(&rawUUIDStr);
#else
    uuid_t uuid;
    uuid_generate_random(uuid);

    UUID ret;
    ret.m_strLen = 36;
    uuid_unparse(uuid, &ret.m_str[0]);
#endif
    return ret;
}
    
inline UUID::ConstIteratorType UUID::Begin() const noexcept
{
    return this->CBegin();
}

inline UUID::ConstIteratorType UUID::End() const noexcept
{
    return this->CEnd();
}
   
inline const char UUID::operator[](int32_t index) const
{
    return SuperType::operator[](index);
}

} /* namespace tgon */
