/**
 * @file    StringHash.h
 * @author  ggomdyu
 * @date    09/25/2018
 */

#pragma once
#include <string>
#include <string_view>

#include "Core/TypeTraits.h"

#include "Hash.h"
#include "FixedString.h"

namespace tgon
{
namespace detail
{

template <typename _DeriviedType>
class BaseBasicStringHash
{
/**@section Constructor */
public:
    /**@brief   Initializes with null character pointer. */
    constexpr BaseBasicStringHash() noexcept :
        m_hashCode(0)
    {
    }

    template <typename _ValueType>
    constexpr BaseBasicStringHash(const _ValueType& str) noexcept :
        m_hashCode(X65599Hash(str))
    {
    }

/**@section Operator */
public:
    constexpr bool operator==(const _DeriviedType& rhs) const noexcept
    {
        return reinterpret_cast<_DeriviedType*>(this)->GetHashCode() == rhs.GetHashCode();
    }

    constexpr bool operator!=(const _DeriviedType& rhs) const noexcept
    {
        return !this->operator==(rhs);
    }

/**@section Method */
public:
    /**@brief   Gets the hash code of the string. */
    constexpr const size_t GetHashCode() const noexcept
    {
        return m_hashCode;
    }

    void Clear()
    {

    }

/**@section Variable */
private:
    size_t m_hashCode;
};

} /* namespace detail */
    
template <typename _StringType, typename _EnableType = void>
class BasicStringHash :
    public detail::BaseBasicStringHash<BasicStringHash<_StringType, _EnableType>>
{
/**@section Type */
public:
    using ValueType = typename _StringType::ValueType;
    using StringType = _StringType;
    
/**@section Constructor */
public:
    /**@brief   Initializes with null character pointer. */
    constexpr BasicStringHash() noexcept :
        BasicStringHash(nullptr, 0)
    {
    }
    
    /**@brief   Initializes with character array. */
    template <std::size_t _CharArraySize>
    constexpr BasicStringHash(const ValueType(&str)[_CharArraySize]) noexcept :
        BasicStringHash(str, _CharArraySize - 1)
    {
    }

    /**@brief   Initializes with string_view. */
    constexpr BasicStringHash(const std::basic_string_view<ValueType>& str) noexcept :
        BasicStringHash(str.data()),
        m_str(str, str.length())
    {
    }
    
    /**@brief   Initializes with string. */
    constexpr BasicStringHash(const _StringType& str) noexcept :
        m_str(str)
    {
    }
    
/**@section Method */
public:
    /**@brief   Gets the character pointer to string. */
    constexpr const ValueType* CStr() const noexcept
    {
        return m_str.CStr();
    }
    
    /**@brief   Gets the length of string. */
    constexpr const size_t Length() const noexcept
    {
        return m_str.Length();
    }

    void Clear()
    {
        m_str.Clear();
    }

/**@section Variable */
private:
    _StringType m_str;
};

template <typename _StringType>
class BasicStringHash<_StringType, typename std::enable_if<IsCharPointerTypeValue<_StringType>>::type> :
    public detail::BaseBasicStringHash<BasicStringHash<_StringType, typename std::enable_if<IsCharPointerTypeValue<_StringType>>::type>>
{
/**@section Type */
public:
    using ValueType = PureType<_StringType>;
    using StringType = _StringType;
    
/**@section Constructor */
public:
    /**@brief   Initializes with null character pointer. */
    constexpr BasicStringHash() noexcept :
        BasicStringHash(nullptr, 0)
    {
    }
    
    /**@brief   Initializes with character pointer. */
    template <std::size_t _CharArraySize>
    constexpr BasicStringHash(const ValueType(&str)[_CharArraySize]) noexcept :
        BasicStringHash(str, _CharArraySize - 1)
    {
    }
    
    /**@brief   Initializes with string_view. */
    constexpr BasicStringHash(const std::basic_string_view<ValueType>& str) noexcept :
        m_str(str),
        m_strLen(str.length())
    {
    }
    
/**@section Method */
public:
    /**@brief   Gets the character pointer to string. */
    constexpr const _StringType& CStr() const noexcept
    {
        return m_str;
    }

    /**@brief   Gets the length of string. */
    constexpr const size_t Length() const noexcept
    {
        return m_strLen;
    }

    void Clear()
    {
    }

/**@section Variable */
private:
    _StringType m_str;
    size_t m_strLen;
    size_t m_hashCode;
};

template <typename _StringType>
class BasicStringHash<_StringType, typename std::enable_if<IsBasicStringValue<_StringType> || IsBasicStringViewValue<_StringType>>::type> :
    public detail::BaseBasicStringHash<BasicStringHash<_StringType, typename std::enable_if<IsBasicStringValue<_StringType> || IsBasicStringViewValue<_StringType>>::type>>
{
/**@section Type */
public:
    using ValueType = typename _StringType::value_type;
    using StringType = _StringType;
    
/**@section Constructor */
public:
    /**@brief   Initializes with null character pointer. */
    constexpr BasicStringHash() noexcept = default;
    
    /**@brief   Initializes with character array. */
    template <std::size_t _CharArraySize>
    constexpr BasicStringHash(const ValueType(&str)[_CharArraySize]) noexcept :
        BasicStringHash({str, _CharArraySize - 1})
    {
    }

    /**@brief   Initializes with basic_string. */
    constexpr BasicStringHash(const _StringType& str) noexcept :
        m_str(str)
    {
    }
    
/**@section Method */
public:
    /**@brief   Gets the character pointer to string. */
    constexpr const ValueType* CStr() const noexcept
    {
        return m_str.c_str();
    }
    
    /**@brief   Gets the length of string. */
    constexpr const size_t Length() const noexcept
    {
        return m_str.length();
    }

    void Clear()
    {
    }

/**@section Variable */
private:
    _StringType m_str;
};

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
