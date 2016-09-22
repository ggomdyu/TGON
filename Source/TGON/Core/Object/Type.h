/*
* Author : Cha Junho
* Date : 04/19/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Platform/PlatformInclude.h"

#include <string>
#include <cstdint>


namespace tgon
{


class TGON_API Type final
{
	// 
	// Ctor/Dtor
	// 
public:
	/*
	 * @note		Save type name and hash key
	 * @param name	Type name
	*/
	explicit Type( const std::string& name );
	~Type( );

	// 
	// Operators
	// 
	/*
	 * @note		Now	we can insert this structure to std::map
	 * @param	rhs	Compare target
	*/
	bool operator<( const Type& rhs ) const;

	// 
	// Gets
	// 
public:
	/* @return	Return stored hase code */
	uint32_t GetHashCode( ) const;

	/* @return	Return name as const reference */
	const std::string& GetName( ) const;

	// 
	// Private variables
	// 
private:
	// Type name as string value
	const std::string m_name;

	// Hash value of m_name
	const uint32_t m_hashCode;
};


inline uint32_t Type::GetHashCode( ) const
{
	return m_hashCode;
}

inline const std::string& Type::GetName( ) const
{
	return m_name;
}

inline bool Type::operator<( const Type& rhs ) const
{
	return m_hashCode < rhs.m_hashCode;
}


} /*namespace tgon*/