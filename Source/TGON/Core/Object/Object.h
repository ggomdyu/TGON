/*
* Author : Cha Junho
* Date : 03/22/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Platform/PlatformInclude.h"
#include "Type.h"

#include <cstdint>


namespace tgon
{


class TGON_API Object 
{
	// 
	// Type definitions
	// 
public:
	using Super = void;
	using This = Object;

	// 
	// Opeators
	// 
	bool operator==( const Object& rhs ) const
	{
		return this->Equals( rhs );
	}
	bool operator!=( const Object& rhs ) const
	{
		return !( *this == rhs );
	}

	// 
	// Commands
	// 
public:
	static bool Equals( const Object& lhs, const Object& rhs )
	{
		return lhs.Equals( rhs );
	}
	
	/*
	 * @note Compare two instance. This can be overridden.
	 * @return Return true if both refer to the same object.
	*/
	virtual bool Equals( const Object& rhs ) const
	{
		return ( this->GetHashCode( ) == rhs.GetHashCode( ));
	}

	/* @note Compare two instance.
	 * @param lhs Left handling side
	 * @param rhs Right handling side
	 * @return Return true if both refer to the same object.
	*/
	static bool ReferenceEquals( const Object& lhs, const Object& rhs )
	{
		return ( &lhs == &rhs );
	}

	// 
	// Gets
	// 
	/* @return Return dynamic bound type's hash code. */
	virtual uint32_t GetHashCode( ) const = 0;
	
	/* @return Return dynamic bound type's name. */
	virtual const char* GetName( ) const = 0;

	// 
	// Ctor/Dtor
	// 
public:
	Object( );
	virtual ~Object( ) = 0;
};


} /* namespace tgon */



#define TGON_GENERATE_OBJECT_INTERFACE( subclassType, superclassType )\
	using This = subclassType;\
	using Super = superclassType;\
	\
	virtual uint32_t GetHashCode( ) const override\
	{\
		return tgon::GetType<This>().GetHashCode( );\
	}\
	virtual const char* GetName( ) const override\
	{\
		return tgon::GetType<This>().GetName( ).c_str( );\
	}