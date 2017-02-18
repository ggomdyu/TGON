/**
 * filename Type.h
 * author   ggomdyu
 * since    03/14/2016
 */

#pragma once
#include <string>
#include <cstdint>

namespace tgon
{

struct TypeInfo
{
/**
 * @section Ctor/Dtor
 */
public:
    template <std::size_t N>
    TypeInfo(const char(&)[N]) noexcept;

    TypeInfo(const char* name, int length) noexcept;

    TypeInfo(const std::string& name) noexcept;

/**
 * @section Gets
 */
public:
	/* @return	Hash value of the type name. */
    uint32_t GetHashCode() const noexcept;
	
    /* @return	The type name */
    const std::string& GetName() const noexcept;

/**
 * @section Private variables
 */
private:
	const std::string m_name;
    const uint32_t m_hashCode;
};

template<std::size_t N>
inline tgon::TypeInfo::TypeInfo(const char(&name)[N]) noexcept :
    TypeInfo(name, N)
{
}

} /*namespace tgon*/