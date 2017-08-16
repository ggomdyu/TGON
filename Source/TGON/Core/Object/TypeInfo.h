/**
 * @filename    TypeInfo.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include <cstdint>

namespace tgon
{
namespace object
{

struct TypeInfo final
{
/* @section Ctor/Dtor */
public:
    template <std::size_t _CharArraySize>
    constexpr TypeInfo(const char(&typeName)[_CharArraySize], const TypeInfo* superType) noexcept;

/* @section Public method */
public:
    std::size_t GetHashCode() const noexcept;
    constexpr const char* GetName() const noexcept;
    
    constexpr const TypeInfo& GetSuperType() const noexcept;

/* @section Private variable */
private:
    const char* m_name;
    const TypeInfo* m_superType;
};

template <std::size_t _CharArraySize>
constexpr TypeInfo::TypeInfo(const char(&typeName)[_CharArraySize], const TypeInfo* superType) noexcept :
    m_name(typeName),
    m_superType(superType)
{
}

inline std::size_t TypeInfo::GetHashCode() const noexcept
{
    return reinterpret_cast<std::size_t>(this);
}

constexpr const char* TypeInfo::GetName() const noexcept
{
    return m_name;
}

constexpr const TypeInfo& TypeInfo::GetSuperType() const noexcept
{
    return *m_superType;
}

} /* namespace object */
} /* namespace tgon */
