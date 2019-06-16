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
    constexpr BaseBasicStringHash() noexcept :
        m_hashCode(0)
    {
    }

    template <typename _ValueType, typename std::enable_if_t<IsCharPointerTypeValue<_ValueType>>* = nullptr>
    constexpr BaseBasicStringHash(const _ValueType& str) noexcept :
        m_hashCode(X65599Hash(str))
    {
    }

    constexpr BaseBasicStringHash(uint32_t hashCode) noexcept :
        m_hashCode(hashCode)
    {
    }

/**@section Operator */
public:
    constexpr bool operator==(const _DeriviedType& rhs) const noexcept
    {
        return m_hashCode == rhs.GetHashCode();
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

protected:
    void Clear()
    {
        m_hashCode = 0;
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
    using SuperType = detail::BaseBasicStringHash<BasicStringHash<_StringType, _EnableType>>;
    using StringType = _StringType;
    
/**@section Constructor */
public:
    /**@brief   Initializes with null character pointer. */
    constexpr BasicStringHash() noexcept :
        BasicStringHash(nullptr, 0)
    {
    }
    
    /**@brief   Initializes with character array. */
    template <std::size_t _CharBufferLen>
    constexpr BasicStringHash(const ValueType(&str)[_CharBufferLen]) noexcept :
        BasicStringHash({str, _CharBufferLen - 1})
    {
    }

    /**@brief   Initializes with string_view. */
    constexpr BasicStringHash(const std::basic_string_view<ValueType>& str) noexcept :
        SuperType(str.data()),
        m_str(str)
    {
    }
    
    /**@brief   Initializes with BasicStringHash. */
    template <typename _StringType2, typename std::enable_if_t<std::is_base_of_v<detail::BaseBasicStringHash<_StringType2>, _StringType2>>* = nullptr>
    constexpr BasicStringHash(const _StringType2& str) noexcept :
        SuperType(str.GetHashCode()),
        m_str({str.CStr(), str.Length()})
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
        SuperType::Clear();
        m_str.Clear();
    }

/**@section Variable */
private:
    _StringType m_str;
};

template <typename _StringType>
class BasicStringHash<_StringType, typename std::enable_if_t<IsBasicStringValue<_StringType> || IsBasicStringViewValue<_StringType>>> :
    public detail::BaseBasicStringHash<BasicStringHash<_StringType, typename std::enable_if_t<IsBasicStringValue<_StringType> || IsBasicStringViewValue<_StringType>>>>
{
/**@section Type */
public:
    using ValueType = typename _StringType::value_type;
    using SuperType = detail::BaseBasicStringHash<BasicStringHash<_StringType, typename std::enable_if_t<IsBasicStringValue<_StringType> || IsBasicStringViewValue<_StringType>>>>;
    using StringType = _StringType;
    
/**@section Constructor */
public:
    /**@brief   Initializes with null character pointer. */
    constexpr BasicStringHash() noexcept = default;
    
    /**@brief   Initializes with character array. */
    template <std::size_t _CharBufferLen>
    constexpr BasicStringHash(const ValueType(&str)[_CharBufferLen]) noexcept :
        BasicStringHash({str, _CharBufferLen - 1})
    {
    }

    /**@brief   Initializes with basic_string. */
    constexpr BasicStringHash(const std::basic_string_view<ValueType>& str) noexcept :
        SuperType(str.data()),
        m_str(str)
    {
    }
    
    /**@brief   Initializes with BasicStringHash. */
    template <typename _StringType2, typename std::enable_if_t<std::is_base_of_v<detail::BaseBasicStringHash<_StringType2>, _StringType2>>* = nullptr>
    constexpr BasicStringHash(const _StringType2& str) noexcept :
        SuperType(str.GetHashCode()),
        m_str({str.CStr(), str.Length()})
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
        SuperType::Clear();
        m_str.clear();
    }

/**@section Variable */
private:
    _StringType m_str;
};

template <typename _StringType>
class BasicStringHash<_StringType, typename std::enable_if_t<IsCharPointerTypeValue<_StringType>>> :
    public detail::BaseBasicStringHash<BasicStringHash<_StringType, typename std::enable_if_t<IsCharPointerTypeValue<_StringType>>>>
{
/**@section Type */
public:
    using ValueType = PureType<_StringType>;
    using SuperType = detail::BaseBasicStringHash<BasicStringHash<_StringType, typename std::enable_if_t<IsCharPointerTypeValue<_StringType>>>>;
    using StringType = _StringType;
    
/**@section Constructor */
public:
    /**@brief   Initializes with null character pointer. */
    constexpr BasicStringHash() noexcept :
        BasicStringHash(nullptr, 0)
    {
    }
    
    /**@brief   Initializes with character pointer. */
    template <std::size_t _CharBufferLen>
    constexpr BasicStringHash(const ValueType(&str)[_CharBufferLen]) noexcept :
        BasicStringHash({str, _CharBufferLen - 1})
    {
    }
    
    /**@brief   Initializes with string_view. */
    constexpr BasicStringHash(const std::basic_string_view<ValueType>& str) noexcept :
        SuperType(str.data()),
        m_str(str.data()),
        m_strLen(str.length())
    {
    }
    
    /**@brief   Initializes with BasicStringHash. */
    template <typename _StringType2, typename std::enable_if_t<std::is_base_of_v<detail::BaseBasicStringHash<_StringType2>, _StringType2>>* = nullptr>
    constexpr BasicStringHash(const _StringType2& str) noexcept :
        SuperType(str.GetHashCode()),
        m_str(str.CStr()),
        m_strLen(str.Length())
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
        SuperType::Clear();
        m_str = "";
        m_strLen = 0;
    }

/**@section Variable */
private:
    _StringType m_str;
    size_t m_strLen;
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

namespace std
{

template<typename _StringType>
struct hash<tgon::BasicStringHash<_StringType>>
{
/* @section Method */
public:
    size_t operator()(const tgon::BasicStringHash<_StringType>& rhs) const noexcept
    {
        return rhs.GetHashCode();
    }
};

} /* namespace std */
