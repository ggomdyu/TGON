/**
 * @filename    TypeInfo.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include <cstdint>

#include "Core/Hash/Hash.h"

namespace tgon
{
namespace object
{

struct TypeInfo
{
/* @section Ctor/Dtor */
public:
    template <std::size_t _CharArraySize>
    constexpr explicit TypeInfo(const char(&typeName)[_CharArraySize]) noexcept;

/* @section Public method */
public:
    constexpr std::size_t GetHashCode() const;

    constexpr const char* GetName() const noexcept;

/* @section Private variable */
private:
    const char* m_typeName;
};

template <std::size_t _CharArraySize>
constexpr TypeInfo::TypeInfo(const char(&typeName)[_CharArraySize]) noexcept :
    m_typeName(typeName)
{
}

constexpr std::size_t TypeInfo::GetHashCode() const
{
    return hash::x65599Hash(m_typeName);
}

constexpr const char* TypeInfo::GetName() const noexcept
{
    return m_typeName;
}

} /* namespace object */
} /* namespace tgon */
