/**
 * @filename    TypeInfo.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include <string>
#include <cstdint>

namespace tgon
{
namespace object
{

struct TypeInfo
{
/**
 * @section Ctor/Dtor
 */
public:
    template <std::size_t N>
    TypeInfo(const char(&)[N]) noexcept;
    TypeInfo(const char* name, std::size_t length) noexcept;
    TypeInfo(const std::string& name) noexcept;

/**
 * @section Public method
 */
public:
    /* @return  The hash value of the type name. */
    std::size_t GetHashCode() const noexcept;
    
    /* @return  The name of type */
    const std::string& GetTypeName() const noexcept;
    
/**
 * @section Private variable
 */
private:
    const std::string m_typeName;
    const std::size_t m_hashCode;
};

template<std::size_t N>
inline TypeInfo::TypeInfo(const char(&name)[N]) noexcept :
    TypeInfo(name, N)
{
}

} /* namespace object */
} /* namespace tgon */
