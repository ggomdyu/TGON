/**
 * @filename    TypeInfo.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include <cstdint>
#include "Core/String/BuiltinReadOnlyString.h"

namespace tgon
{
namespace object
{

template <std::size_t _TypeNameLength>
struct TypeInfo
{
/* @section Ctor/Dtor */
public:
    constexpr explicit TypeInfo(const char(&typeName)[_TypeNameLength]);

/* @section Public method */
public:
    constexpr std::size_t GetHashCode() const;
    constexpr const string::BuiltinReadOnlyString<char, _TypeNameLength>& GetTypeName() const noexcept;

/* @section Private variable */
private:
    string::BuiltinReadOnlyString<char, _TypeNameLength> m_typeName;
};

template<std::size_t _TypeNameLength>
constexpr TypeInfo<_TypeNameLength>::TypeInfo(const char(&typeName)[_TypeNameLength]) :
    m_typeName(m_typeName)
{
}

template<std::size_t _TypeNameLength>
constexpr std::size_t TypeInfo<_TypeNameLength>::GetHashCode() const
{
    return hash::x65599Hash(m_typeName.CStr());
}

template<std::size_t _TypeNameLength>
constexpr const string::BuiltinReadOnlyString<char, _TypeNameLength>& TypeInfo<_TypeNameLength>::GetTypeName() const noexcept
{
    return m_typeName;
}

} /* namespace object */
} /* namespace tgon */
