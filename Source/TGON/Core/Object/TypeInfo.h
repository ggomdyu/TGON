/**
 * @filename    TypeInfo.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include <cstdint>

#include "Core/Hash/Hash.h"
#include "Core/String/FixedString.h"

namespace tgon
{
namespace object
{

template <typename _TypeNameCharType, std::size_t _TypeNameLength>
struct TypeInfo
{
/* @section Ctor/Dtor */
public:
    constexpr explicit TypeInfo(const char(&typeName)[_TypeNameLength]);

/* @section Public method */
public:
    constexpr std::size_t GetHashCode() const;
    constexpr const string::BasicFixedString<char, _TypeNameLength>& GetTypeName() const noexcept;

/* @section Private variable */
private:
    char m_typeName[_TypeNameLength];
};

template <typename _TypeNameCharType, std::size_t _TypeNameLength>
constexpr TypeInfo<_TypeNameCharType, _TypeNameLength>::TypeInfo(const char(&typeName)[_TypeNameLength])
{
    for (std::size_t i = 0; i < _TypeNameLength; ++i)
    {
        m_typeName[i] = typeName[i];
    }
}

template <typename _TypeNameCharType, std::size_t _TypeNameLength>
constexpr std::size_t TypeInfo<_TypeNameCharType, _TypeNameLength>::GetHashCode() const
{
    return hash::x65599Hash("");
}

template <typename _TypeNameCharType, std::size_t _TypeNameLength>
constexpr const string::BasicFixedString<char, _TypeNameLength>& TypeInfo<_TypeNameCharType, _TypeNameLength>::GetTypeName() const noexcept
{
    return "";
}

} /* namespace object */
} /* namespace tgon */
