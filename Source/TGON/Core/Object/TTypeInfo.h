/**
 * @filename    TTypeInfo.h
 * @author      ggomdyu
 * since        03/14/2016
 */

#pragma once
#include <string>
#include <cstdint>

namespace tgon {
namespace object {

struct TTypeInfo
{
/**
 * @section Ctor/Dtor
 */
public:
    template <std::size_t N>
    TTypeInfo(const char(&)[N]) noexcept;
    TTypeInfo(const char* name, std::size_t length) noexcept;
    TTypeInfo(const std::string& name) noexcept;

/**
 * @section Get method
 */
public:
	/* @return  The hash value of the type name. */
    std::size_t GetHashCode() const noexcept;
	
    /* @return  The name of type */
    const std::string& GetName() const noexcept;

/**
 * @section Private variable
 */
private:
	const std::string m_name;
    const std::size_t m_hashCode;
};

template<std::size_t N>
inline TTypeInfo::TTypeInfo(const char(&name)[N]) noexcept :
    TTypeInfo(name, N)
{
}

} /* namespace object */
} /* namespace tgon */