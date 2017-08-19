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
    constexpr TypeInfo(const char(&typeName)[_CharArraySize], std::size_t typeHashCode, const TypeInfo* superType) noexcept;

    template <std::size_t _CharArraySize>
    constexpr TypeInfo(const char(&typeName)[_CharArraySize], const TypeInfo* superType) noexcept;

/* @section Public method */
public:
    constexpr std::size_t GetHashCode() const noexcept;
    constexpr const char* GetName() const noexcept;

    constexpr const TypeInfo& GetSuperTypeInfo() const noexcept;

/* @section Private variable */
private:
    const char* m_name;
    const std::size_t m_hashCode;

    const TypeInfo* m_superTypeInfo;
};

template <std::size_t _CharArraySize>
constexpr TypeInfo::TypeInfo(const char(&typeName)[_CharArraySize], std::size_t typeHashCode, const TypeInfo* superTypeInfo) noexcept :
    m_name(typeName),
    m_hashCode(typeHashCode),
    m_superTypeInfo(superTypeInfo)
{
}

template <std::size_t _CharArraySize>
constexpr TypeInfo::TypeInfo(const char(&typeName)[_CharArraySize], const TypeInfo* superTypeInfo) noexcept :
#ifdef _MSC_VER
    m_name(typeName),
    m_hashCode(reinterpret_cast<std::size_t>(this)),
    m_superTypeInfo(superType)
#else
    TypeInfo(typeName, reinterpret_cast<std::size_t>(this), superTypeInfo)
#endif
{
}

constexpr const TypeInfo& TypeInfo::GetSuperTypeInfo() const noexcept
{
    return *m_superTypeInfo;
}

constexpr std::size_t TypeInfo::GetHashCode() const noexcept
{
    return m_hashCode;
}

constexpr const char* TypeInfo::GetName() const noexcept
{
    return m_name;
}

} /* namespace object */
} /* namespace tgon */
