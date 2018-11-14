/**
 * @file    StringHash.h
 * @author  ggomdyu
 * @date    09/25/2018
 */

#pragma once
#include <string>

#include "Core/Object/TypeTraits.h"
#include "Core/Hash/Hash.h"

#include "FixedString.h"
#include "StringView.h"

namespace tgon
{
namespace detail
{

template <typename _DeriviedType>
class BasicStringHashImpl
{
/**@section Public operator */
public:
    constexpr bool operator==(const _DeriviedType& rhs) const noexcept;
    constexpr bool operator!=(const _DeriviedType& rhs) const noexcept;
};

template<typename _DeriviedType>
constexpr bool BasicStringHashImpl<_DeriviedType>::operator==(const _DeriviedType& rhs) const noexcept
{
    return reinterpret_cast<_DeriviedType*>(this)->GetHashCode() == rhs.GetHashCode();
}

template<typename _DeriviedType>
constexpr bool BasicStringHashImpl<_DeriviedType>::operator!=(const _DeriviedType& rhs) const noexcept
{
    return !this->operator==(rhs);
}

} /* namespace detail */
    
template <typename _StringType, typename _EnableType = void>
class BasicStringHash :
    public detail::BasicStringHashImpl<BasicStringHash<_StringType, _EnableType>>
{
/**@section Public type */
public:
    using ValueType = typename _StringType::ValueType;
    using StringType = _StringType;
    
/**@section Public constructor */
public:
    /**@brief   Initializes with null character pointer. */
    constexpr BasicStringHash() noexcept;
    
    /**@brief   Initializes with character pointer. */
    template <std::size_t _CharArraySize>
    constexpr BasicStringHash(const ValueType(&str)[_CharArraySize]) noexcept;
    
    /**@brief   Initializes with character pointer and its length. */
    constexpr BasicStringHash(const ValueType* str, size_t strLen) noexcept;
    
    /**@brief   Initializes with string. */
    constexpr BasicStringHash(const _StringType& str) noexcept;
    
/**@section Public method */
public:
    /**@brief   Gets the character pointer to string. */
    constexpr const ValueType* CStr() const noexcept;
    
    /**@brief   Gets the length of string. */
    constexpr const size_t Length() const noexcept;
    
    /**@brief   Gets the hash code of the string. */
    constexpr const size_t GetHashCode() const noexcept;
    
/**@section Private variable */
private:
    _StringType m_str;
    size_t m_hashCode;
};

template <typename _StringType, typename _EnableType>
constexpr BasicStringHash<_StringType, _EnableType>::BasicStringHash() noexcept :
    BasicStringHash(nullptr, 0)
{
}

template <typename _StringType, typename _EnableType>
template <std::size_t _CharArraySize>
constexpr BasicStringHash<_StringType, _EnableType>::BasicStringHash(const ValueType(&str)[_CharArraySize]) noexcept :
    BasicStringHash(str, _CharArraySize - 1)
{
}

template <typename _StringType, typename _EnableType>
constexpr BasicStringHash<_StringType, _EnableType>::BasicStringHash(const ValueType* str, size_t strLen) noexcept :
    m_str(str, strLen),
    m_hashCode(X65599Hash(str))
{
}

template <typename _StringType, typename _EnableType>
constexpr BasicStringHash<_StringType, _EnableType>::BasicStringHash(const _StringType& str) noexcept :
    m_str(str),
    m_hashCode(X65599Hash(str.c_str()))
{
}

template <typename _StringType, typename _EnableType>
constexpr const typename _StringType::ValueType* BasicStringHash<_StringType, _EnableType>::CStr() const noexcept
{
    return m_str.CStr();
}

template <typename _StringType, typename _EnableType>
constexpr const size_t BasicStringHash<_StringType, _EnableType>::Length() const noexcept
{
    return m_str.Length();
}

template <typename _StringType, typename _EnableType>
constexpr const size_t BasicStringHash<_StringType, _EnableType>::GetHashCode() const noexcept
{
    return m_hashCode;
}

template <typename _StringType>
class BasicStringHash<_StringType, typename std::enable_if<IsCharPointerTypeValue<_StringType>>::type> :
    public detail::BasicStringHashImpl<BasicStringHash<_StringType, typename std::enable_if<IsCharPointerTypeValue<_StringType>>::type>>
{
/**@section Public type */
public:
    using ValueType = PurifyType<_StringType>;
    using StringType = _StringType;
    
/**@section Public constructor */
public:
    /**@brief   Initializes with null character pointer. */
    constexpr BasicStringHash() noexcept;
    
    /**@brief   Initializes with character pointer. */
    template <std::size_t _CharArraySize>
    constexpr BasicStringHash(const ValueType(&str)[_CharArraySize]) noexcept;
    
    /**@brief   Initializes with character pointer and its length. */
    constexpr BasicStringHash(const ValueType* str, size_t strLen) noexcept;
    
/**@section Public method */
public:
    /**@brief   Gets the character pointer to string. */
    constexpr const _StringType& CStr() const noexcept;
    
    /**@brief   Gets the length of string. */
    constexpr const size_t Length() const noexcept;
    
    /**@brief   Gets the hash code of the string. */
    constexpr const size_t GetHashCode() const noexcept;
    
/**@section Private variable */
private:
    _StringType m_str;
    size_t m_strLen;
    size_t m_hashCode;
};

template <typename _StringType>
constexpr BasicStringHash<_StringType, typename std::enable_if<IsCharPointerTypeValue<_StringType>>::type>::BasicStringHash() noexcept :
    BasicStringHash(nullptr, 0)
{
}

template <typename _StringType>
template <std::size_t _CharArraySize>
constexpr BasicStringHash<_StringType, typename std::enable_if<IsCharPointerTypeValue<_StringType>>::type>::BasicStringHash(const ValueType(&str)[_CharArraySize]) noexcept :
    BasicStringHash(str, _CharArraySize - 1)
{
}

template <typename _StringType>
constexpr BasicStringHash<_StringType, typename std::enable_if<IsCharPointerTypeValue<_StringType>>::type>::BasicStringHash(const ValueType* str, size_t strLen) noexcept :
    m_str(str),
    m_strLen(strLen),
    m_hashCode(X65599Hash(str))
{
}

template <typename _StringType>
constexpr const _StringType& BasicStringHash<_StringType, typename std::enable_if<IsCharPointerTypeValue<_StringType>>::type>::CStr() const noexcept
{
    return m_str;
}

template <typename _StringType>
constexpr const size_t BasicStringHash<_StringType, typename std::enable_if<IsCharPointerTypeValue<_StringType>>::type>::Length() const noexcept
{
    return m_strLen;
}

template <typename _StringType>
constexpr const size_t BasicStringHash<_StringType, typename std::enable_if<IsCharPointerTypeValue<_StringType>>::type>::GetHashCode() const noexcept
{
    return m_hashCode;
}

template <typename _StringType>
class BasicStringHash<_StringType, typename std::enable_if<IsBasicStringValue<_StringType>>::type> :
    public detail::BasicStringHashImpl<BasicStringHash<_StringType, typename std::enable_if<IsBasicStringValue<_StringType>>::type>>
{
/**@section Public type */
public:
    using ValueType = typename _StringType::value_type;
    using StringType = _StringType;
    
/**@section Public constructor */
public:
    /**@brief   Initializes with null character pointer. */
    BasicStringHash() noexcept;
    
    /**@brief   Initializes with character pointer. */
    template <std::size_t _CharArraySize>
    BasicStringHash(const ValueType(&str)[_CharArraySize]) noexcept;
    
    /**@brief   Initializes with character pointer and its length. */
    BasicStringHash(const ValueType* str, size_t strLen) noexcept;
    
    /**@brief   Initializes with basic_string. */
    BasicStringHash(const _StringType& str) noexcept;
    
/**@section Public method */
public:
    /**@brief   Gets the character pointer to string. */
    const ValueType* CStr() const noexcept;
    
    /**@brief   Gets the length of string. */
    const size_t Length() const noexcept;
    
    /**@brief   Gets the hash code of the string. */
    const size_t GetHashCode() const noexcept;
    
/**@section Private variable */
private:
    _StringType m_str;
    size_t m_hashCode;
};

template <typename _StringType>
inline BasicStringHash<_StringType, typename std::enable_if<IsBasicStringValue<_StringType>>::type>::BasicStringHash() noexcept :
    m_hashCode(0)
{
}

template <typename _StringType>
template <std::size_t _CharArraySize>
inline BasicStringHash<_StringType, typename std::enable_if<IsBasicStringValue<_StringType>>::type>::BasicStringHash(const ValueType(&str)[_CharArraySize]) noexcept :
    BasicStringHash(str, _CharArraySize - 1)
{
}

template <typename _StringType>
inline BasicStringHash<_StringType, typename std::enable_if<IsBasicStringValue<_StringType>>::type>::BasicStringHash(const ValueType* str, size_t strLen) noexcept :
    m_str(str, strLen),
    m_hashCode(X65599Hash(str))
{
}

template <typename _StringType>
inline BasicStringHash<_StringType, typename std::enable_if<IsBasicStringValue<_StringType>>::type>::BasicStringHash(const _StringType& str) noexcept :
    m_str(str),
    m_hashCode(X65599Hash(str.c_str()))
{
}

template <typename _StringType>
inline const typename _StringType::value_type* BasicStringHash<_StringType, typename std::enable_if<IsBasicStringValue<_StringType>>::type>::CStr() const noexcept
{
    return m_str.c_str();
}

template <typename _StringType>
inline const size_t BasicStringHash<_StringType, typename std::enable_if<IsBasicStringValue<_StringType>>::type>::Length() const noexcept
{
    return m_str.length();
}

template <typename _StringType>
inline const size_t BasicStringHash<_StringType, typename std::enable_if<IsBasicStringValue<_StringType>>::type>::GetHashCode() const noexcept
{
    return m_hashCode;
}

using StringHash = BasicStringHash<std::string>;
using WStringHash = BasicStringHash<std::wstring>;
    
using StringViewHash = BasicStringHash<StringView>;
using WStringViewHash = BasicStringHash<WStringView>;

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
