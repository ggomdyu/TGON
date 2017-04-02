/**
 * filename TTypeInfo.h
 * author   ggomdyu
 * since    03/14/2016
 */

#pragma once
#include <string>
#include <cstdint>

namespace tgon
{

struct TTypeInfo
{
/**
 * @section Ctor/Dtor
 */
public:
    template <std::size_t N>
    TTypeInfo(const char(&)[N]) noexcept;

    TTypeInfo(const char* name, int length) noexcept;

    TTypeInfo(const std::string& name) noexcept;

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
inline tgon::TTypeInfo::TTypeInfo(const char(&name)[N]) noexcept :
    TTypeInfo(name, N)
{
}

} /* namespace tgon */