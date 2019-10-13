/**
 * @file    StringHash.h
 * @author  ggomdyu
 * @date    09/25/2018
 */

#pragma once
#include <string>

#include "Core/TypeTraits.h"

#include "Hash.h"
#include "FixedString.h"

namespace tgon
{
namespace detail
{

template <typename _StringType>
class BaseBasicStringHash
{
/**@section Type */
public:
    using HashCodeType = decltype(X65599Hash(""));
    
/**@section Constructor */
public:
    constexpr BaseBasicStringHash() noexcept;
    template <typename _StringType2>
    constexpr BaseBasicStringHash(_StringType2&& str) noexcept;
    template <typename _StringType2>
    constexpr BaseBasicStringHash(_StringType2&& str, HashCodeType hashCode) noexcept;
    template <typename _StringType2>
    constexpr BaseBasicStringHash(BaseBasicStringHash<_StringType2>&& str) noexcept;
    template <typename _StringType2>
    constexpr BaseBasicStringHash(const BaseBasicStringHash<_StringType2>& str) noexcept;
    
/**@section Operator */
public:
    template <typename _StringType2>
    constexpr bool operator==(const BaseBasicStringHash<_StringType2>& rhs) const noexcept;
    template <typename _StringType2>
    constexpr bool operator!=(const BaseBasicStringHash<_StringType2>& rhs) const noexcept;

/**@section Method */
public:
    constexpr const _StringType& CStr() const noexcept;
    constexpr HashCodeType GetHashCode() const noexcept;
    void Clear();

/**@section Variable */
protected:
    _StringType m_str;
    HashCodeType m_hashCode;
};

template <typename _StringType>
constexpr BaseBasicStringHash<_StringType>::BaseBasicStringHash() noexcept :
    m_str(""),
    m_hashCode(0)
{
}

template <typename _StringType>
template <typename _StringType2>
constexpr BaseBasicStringHash<_StringType>::BaseBasicStringHash(_StringType2&& str) noexcept :
    m_str(std::forward<_StringType2>(str)),
    m_hashCode(X65599Hash(&str[0]))
{
}

template <typename _StringType>
template <typename _StringType2>
constexpr BaseBasicStringHash<_StringType>::BaseBasicStringHash(_StringType2&& str, HashCodeType hashCode) noexcept :
    m_str(std::forward<_StringType2>(str)),
    m_hashCode(hashCode)
{
}

template <typename _StringType>
template <typename _StringType2>
constexpr BaseBasicStringHash<_StringType>::BaseBasicStringHash(BaseBasicStringHash<_StringType2>&& str) noexcept :
    BaseBasicStringHash(std::move(str.m_str), str.GetHashCode())
{
    str.m_hashCode = 0;
}

template <typename _StringType>
template <typename _StringType2>
constexpr BaseBasicStringHash<_StringType>::BaseBasicStringHash(const BaseBasicStringHash<_StringType2>& str) noexcept :
    BaseBasicStringHash(str.m_str, str.GetHashCode())
{
}

template <typename _StringType>
template <typename _StringType2>
constexpr bool BaseBasicStringHash<_StringType>::operator==(const BaseBasicStringHash<_StringType2>& rhs) const noexcept
{
    return m_hashCode == rhs.GetHashCode();
}

template <typename _StringType>
template <typename _StringType2>
constexpr bool BaseBasicStringHash<_StringType>::operator!=(const BaseBasicStringHash<_StringType2>& rhs) const noexcept
{
    return !this->operator==(rhs);
}

template <typename _StringType>
constexpr const _StringType& BaseBasicStringHash<_StringType>::CStr() const noexcept
{
    return &m_str[0];
}

template <typename _StringType>
constexpr typename BaseBasicStringHash<_StringType>::HashCodeType BaseBasicStringHash<_StringType>::GetHashCode() const noexcept
{
    return m_hashCode;
}

template <typename _StringType>
inline void BaseBasicStringHash<_StringType>::Clear()
{
    m_str = {};
    m_hashCode = 0;
}

} /* namespace detail */
    
template <typename _StringType, typename _EnableType = void>
class BasicStringHash :
    public detail::BaseBasicStringHash<_StringType>
{
/**@section Type */
public:
    using ValueType = typename _StringType::ValueType;
    using SuperType = detail::BaseBasicStringHash<_StringType>;
    using StringType = _StringType;
    
/**@section Constructor */
public:
    using SuperType::SuperType;
    
/**@section Method */
public:
    constexpr const int32_t Length() const noexcept;
};

template <typename _StringType, typename _EnableType>
constexpr const int32_t BasicStringHash<_StringType, _EnableType>::Length() const noexcept
{
    return SuperType::m_str.Length();
}

template <typename _StringType>
class BasicStringHash<_StringType, typename std::enable_if_t<IsBasicString<_StringType> || IsBasicStringView<_StringType>>> :
    public detail::BaseBasicStringHash<_StringType>
{
/**@section Type */
public:
    using ValueType = typename _StringType::value_type;
    using StringType = _StringType;
    using SuperType = detail::BaseBasicStringHash<_StringType>;

/**@section Constructor */
public:
    using SuperType::SuperType;
    
    template <typename _StringType2>
    constexpr BasicStringHash(_StringType2&& str) noexcept;
    
/**@section Method */
public:
    constexpr const int32_t Length() const noexcept;
};

template <typename _StringType>
template <typename _StringType2>
constexpr BasicStringHash<_StringType, typename std::enable_if_t<IsBasicString<_StringType> || IsBasicStringView<_StringType>>>::BasicStringHash(_StringType2&& str) noexcept :
    SuperType(str, X65599Hash(&str[0]))
{
}

template <typename _StringType>
constexpr const int32_t BasicStringHash<_StringType, typename std::enable_if_t<IsBasicString<_StringType> || IsBasicStringView<_StringType>>>::Length() const noexcept
{
    return StringType::m_str.length();
}

template <typename _StringType>
class BasicStringHash<_StringType, typename std::enable_if_t<IsCharPointer<_StringType>>> :
    public detail::BaseBasicStringHash<_StringType>
{
/**@section Type */
public:
    using ValueType = Pure<_StringType>;
    using SuperType = detail::BaseBasicStringHash<_StringType>;
    using StringType = _StringType;
    
/**@section Constructor */
public:
    using SuperType::SuperType;
    
    template <typename _StringType2>
    constexpr BasicStringHash(const _StringType2& str) noexcept;
    
/**@section Method */
public:
    constexpr const int32_t Length() const noexcept;
    void Clear();

/**@section Variable */
private:
    int32_t m_strLen;
};

template <typename _StringType>
template <typename _StringType2>
constexpr BasicStringHash<_StringType, typename std::enable_if_t<IsCharPointer<_StringType>>>::BasicStringHash(const _StringType2& str) noexcept :
    SuperType(str, X65599Hash(&str[0])),
    m_strLen([&]()
    {
        if constexpr (IsChar<Pure<_StringType2>>)
        {
            return static_cast<int32_t>(std::char_traits<ValueType>::length(&str[0]));
        }
        else if constexpr (IsBasicString<_StringType> || IsBasicStringView<_StringType>)
        {
            return static_cast<int32_t>(str.length());
        }
        else
        {
            return static_cast<int32_t>(str.Length());
        }
    } ())
{
}

template <typename _StringType>
constexpr const int32_t BasicStringHash<_StringType, typename std::enable_if_t<IsCharPointer<_StringType>>>::Length() const noexcept
{
    return m_strLen;
}

template <typename _StringType>
inline void BasicStringHash<_StringType, typename std::enable_if_t<IsCharPointer<_StringType>>>::Clear()
{
    SuperType::Clear();
    m_strLen = 0;
}

template <typename _Type>
constexpr bool IsBasicStringHashValue = false;

using StringHash = BasicStringHash<std::string>;
using StringViewHash = BasicStringHash<std::string_view>;
using FixedString8Hash = BasicStringHash<FixedString8>;
using FixedString16Hash = BasicStringHash<FixedString16>;
using FixedString32Hash = BasicStringHash<FixedString32>;
using FixedString64Hash = BasicStringHash<FixedString64>;
using FixedString128Hash = BasicStringHash<FixedString128>;
using FixedString256Hash = BasicStringHash<FixedString256>;
using FixedString512Hash = BasicStringHash<FixedString512>;
using FixedString1024Hash = BasicStringHash<FixedString1024>;
using FixedString2048Hash = BasicStringHash<FixedString2048>;
using FixedString4096Hash = BasicStringHash<FixedString4096>;
using FixedString8192Hash = BasicStringHash<FixedString8192>;

using WStringHash = BasicStringHash<std::wstring>;
using WStringViewHash = BasicStringHash<std::wstring_view>;
using WFixedString8Hash = BasicStringHash<WFixedString8>;
using WFixedString16Hash = BasicStringHash<WFixedString16>;
using WFixedString32Hash = BasicStringHash<WFixedString32>;
using WFixedString64Hash = BasicStringHash<WFixedString64>;
using WFixedString128Hash = BasicStringHash<WFixedString128>;
using WFixedString256Hash = BasicStringHash<WFixedString256>;
using WFixedString512Hash = BasicStringHash<WFixedString512>;
using WFixedString1024Hash = BasicStringHash<WFixedString1024>;
using WFixedString2048Hash = BasicStringHash<WFixedString2048>;
using WFixedString4096Hash = BasicStringHash<WFixedString4096>;
using WFixedString8192Hash = BasicStringHash<WFixedString8192>;

using U16StringHash = BasicStringHash<std::u16string>;
using U16StringViewHash = BasicStringHash<std::u16string_view>;
using U16FixedString8Hash = BasicStringHash<U16FixedString8>;
using U16FixedString16Hash = BasicStringHash<U16FixedString16>;
using U16FixedString32Hash = BasicStringHash<U16FixedString32>;
using U16FixedString64Hash = BasicStringHash<U16FixedString64>;
using U16FixedString128Hash = BasicStringHash<U16FixedString128>;
using U16FixedString256Hash = BasicStringHash<U16FixedString256>;
using U16FixedString512Hash = BasicStringHash<U16FixedString512>;
using U16FixedString1024Hash = BasicStringHash<U16FixedString1024>;
using U16FixedString2048Hash = BasicStringHash<U16FixedString2048>;
using U16FixedString4096Hash = BasicStringHash<U16FixedString4096>;
using U16FixedString8192Hash = BasicStringHash<U16FixedString8192>;

using U32StringHash = BasicStringHash<std::u32string>;
using U32StringViewHash = BasicStringHash<std::u32string_view>;
using U32FixedString8Hash = BasicStringHash<U32FixedString8>;
using U32FixedString16Hash = BasicStringHash<U32FixedString16>;
using U32FixedString32Hash = BasicStringHash<U32FixedString32>;
using U32FixedString64Hash = BasicStringHash<U32FixedString64>;
using U32FixedString128Hash = BasicStringHash<U32FixedString128>;
using U32FixedString256Hash = BasicStringHash<U32FixedString256>;
using U32FixedString512Hash = BasicStringHash<U32FixedString512>;
using U32FixedString1024Hash = BasicStringHash<U32FixedString1024>;
using U32FixedString2048Hash = BasicStringHash<U32FixedString2048>;
using U32FixedString4096Hash = BasicStringHash<U32FixedString4096>;
using U32FixedString8192Hash = BasicStringHash<U32FixedString8192>;

namespace detail
{

template <typename>
struct IsBasicStringHash : std::false_type {};

template <typename _StringType>
struct IsBasicStringHash<BasicStringHash<_StringType>> : std::true_type {};

} /* namespace detail */
} /* namespace tgon */

namespace std
{

template <typename _StringType>
struct hash<tgon::BasicStringHash<_StringType>>
{
/* @section Method */
public:
    int32_t operator()(const tgon::BasicStringHash<_StringType>& rhs) const noexcept
    {
        return rhs.GetHashCode();
    }
};

} /* namespace std */
