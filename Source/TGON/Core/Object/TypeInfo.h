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

template <std::size_t TypeNameLength>
struct TypeInfo
{
/* @section Ctor/Dtor */
public:
    explicit TypeInfo(const char(&typeName)[TypeNameLength]);
    TypeInfo(const char* typeName, std::size_t length);

/* @section Private variable */
private:
    string::BasicFixedString<char, TypeNameLength> m_typeName;

/* @section Public method */
public:
    constexpr std::size_t GetHashCode() const;

    constexpr const decltype(m_typeName)& GetTypeName() const noexcept
    {
        return m_typeName;
    }
};

template <std::size_t TypeNameLength>
inline TypeInfo<TypeNameLength>::TypeInfo(const char(&typeName)[TypeNameLength]) :
    m_typeName(typeName)
{
}

template <std::size_t TypeNameLength>
inline TypeInfo<TypeNameLength>::TypeInfo(const char* typeName, std::size_t length) :
    m_typeName(typeName, length)
{
}

template <std::size_t TypeNameLength>
constexpr std::size_t TypeInfo<TypeNameLength>::GetHashCode() const
{
    return hash::x65599Hash(m_typeName.CStr());
}

//template <std::size_t N>
//constexpr const decltype(TypeInfoTest<N>::m_typeName)& TypeInfoTest<N>::GetTypeName() const noexcept
//{
//    return m_typeName;
//}

} /* namespace object */
} /* namespace tgon */
