/**
 * @filename    TypeInfo.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include <cstdint>

#include "Core/String/FixedString.h"
#include "Core/Hash/Hash.h"

namespace tgon
{
namespace object
{

template <std::size_t N>
struct TypeInfo
{
/**
 * @section Ctor/Dtor
 */
public:
    TypeInfo(const char(&typeName)[N]);
    TypeInfo(const char* typeName, std::size_t length);

/**
 * @section Private variable
 */
private:
    string::BasicFixedString<char, N> m_typeName;

/**
 * @section Public method
 */
public:
    constexpr std::size_t GetHashCode() const
    {
        return hash::x65599Hash(m_typeName.CStr());
    }

    constexpr const decltype(m_typeName)& GetTypeName() const noexcept
    {
        return m_typeName;
    }
};

template <std::size_t N>
inline TypeInfo<N>::TypeInfo(const char(&typeName)[N]) :
    m_typeName(typeName)
{
}

template <std::size_t N>
inline TypeInfo<N>::TypeInfo(const char* typeName, std::size_t length) :
    m_typeName(typeName, length)
{
}

//template <std::size_t N>
//constexpr std::size_t TypeInfoTest<N>::GetHashCode() const
//{
//    return 0;//hash::StringToHash(m_typeName);
//}
//`
//template <std::size_t N>
//constexpr const decltype(TypeInfoTest<N>::m_typeName)& TypeInfoTest<N>::GetTypeName() const noexcept
//{
//    return m_typeName;
//}

} /* namespace object */
} /* namespace tgon */
