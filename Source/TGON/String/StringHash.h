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
/**@section Constructor */
public:
    constexpr BaseBasicStringHash() noexcept;
    template <typename _StringType2>
    constexpr BaseBasicStringHash(_StringType2&& str) noexcept;
    template <typename _StringType2>
    constexpr BaseBasicStringHash(_StringType2&& str, uint32_t hashCode) noexcept;
    
    template <typename _StringType2>
    constexpr BaseBasicStringHash(BaseBasicStringHash<_StringType2>&& str) noexcept :
        BaseBasicStringHash(std::move(str.m_str), str.GetHashCode())
    {
        str.m_str = "";
        str.m_hashCode = 0;
    }
    
    template <typename _StringType2>
    constexpr BaseBasicStringHash(const BaseBasicStringHash<_StringType2>& str) noexcept :
        BaseBasicStringHash(str.m_str, str.GetHashCode())
    {
        str.m_str = "";
        str.m_hashCode = 0;
    }
    
/**@section Operator */
public:
    template <typename _StringType2>
    constexpr bool operator==(const BaseBasicStringHash<_StringType2>& rhs) const noexcept;
    template <typename _StringType2>
    constexpr bool operator!=(const BaseBasicStringHash<_StringType2>& rhs) const noexcept;

/**@section Method */
public:
    constexpr const _StringType& CStr() const noexcept;
    constexpr uint32_t GetHashCode() const noexcept;
    void Clear();

/**@section Variable */
protected:
    _StringType m_str;
    uint32_t m_hashCode;
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
constexpr BaseBasicStringHash<_StringType>::BaseBasicStringHash(_StringType2&& str, uint32_t hashCode) noexcept :
    m_str(std::forward<_StringType2>(str)),
    m_hashCode(hashCode)
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
constexpr uint32_t BaseBasicStringHash<_StringType>::GetHashCode() const noexcept
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
    constexpr const int32_t Length() const noexcept
    {
        return SuperType::m_str.Length();
    }
};

template <typename _StringType>
class BasicStringHash<_StringType, typename std::enable_if_t<IsBasicStringValue<_StringType> || IsBasicStringViewValue<_StringType>>> :
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
    constexpr BasicStringHash(_StringType2&& str) noexcept :
        SuperType(str, X65599Hash(&str[0]))
    {
    }
    
/**@section Method */
public:
    constexpr const int32_t Length() const noexcept
    {
        return StringType::m_str.length();
    }
};

template <typename _StringType>
class BasicStringHash<_StringType, typename std::enable_if_t<IsCharPointerValue<_StringType>>> :
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
    constexpr BasicStringHash(const _StringType2& str) noexcept :
        SuperType(str, X65599Hash(&str[0])),
        m_strLen(std::char_traits<ValueType>::length(&str[0]))
    {
    }
    
/**@section Method */
public:
    constexpr const int32_t Length() const noexcept
    {
        return m_strLen;
    }

    void Clear()
    {
        SuperType::Clear();
        m_strLen = 0;
    }

/**@section Variable */
private:
    int32_t m_strLen;
};

template <typename>
struct IsBasicStringHash : std::false_type {};

template <typename _StringType>
struct IsBasicStringHash<BasicStringHash<_StringType>> : std::true_type {};

template <typename _Type>
constexpr bool IsBasicStringHashValue = false;

using StringHash = BasicStringHash<std::string>;
using WStringHash = BasicStringHash<std::wstring>;
    
using StringViewHash = BasicStringHash<std::string_view>;
using WStringViewHash = BasicStringHash<std::wstring_view>;

using FixedString8Hash = BasicStringHash<FixedString8>;
using FixedString16Hash = BasicStringHash<FixedString16>;
using FixedString32Hash = BasicStringHash<FixedString32>;
using FixedString64Hash = BasicStringHash<FixedString64>;
using FixedString128Hash = BasicStringHash<FixedString128>;
using FixedString256Hash = BasicStringHash<FixedString256>;
using FixedString512Hash = BasicStringHash<FixedString512>;
using FixedString1024Hash = BasicStringHash<FixedString1024>;

using FixedWString8Hash = BasicStringHash<FixedWString8>;
using FixedWString16Hash = BasicStringHash<FixedWString16>;
using FixedWString32Hash = BasicStringHash<FixedWString32>;
using FixedWString64Hash = BasicStringHash<FixedWString64>;
using FixedWString128Hash = BasicStringHash<FixedWString128>;
using FixedWString256Hash = BasicStringHash<FixedWString256>;
using FixedWString512Hash = BasicStringHash<FixedWString512>;
using FixedWString1024Hash = BasicStringHash<FixedWString1024>;

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
