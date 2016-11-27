/**
 * Author : Cha Junho
 * Date : 04/19/2016
 * Latest author :
 * Latest date :
 */

#pragma once
#include <string>
#include <cstdint>

namespace tgon
{

struct TypeInfo
{
/**
 * Ctor/Dtor
 */
public:
    template <std::size_t N>
    TypeInfo( const char(&)[N] ) noexcept;
    
    TypeInfo( const std::string& name, const std::size_t length ) noexcept;

/**
 * Gets
 */
public:
	/* @return	Hash value of the type name. */
    uint32_t GetHashCode( ) const;

	/* @return	The type name */
    const std::string& GetName( ) const;

/**
 * Private variables
 */
private:
	const std::string m_name;
	
    const uint32_t m_hashCode;
};

template<std::size_t N>
inline tgon::TypeInfo::TypeInfo( const char( &name )[N] ) noexcept :
    TypeInfo( name, N )
{
}

} /*namespace tgon*/