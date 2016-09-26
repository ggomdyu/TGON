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
	bool operator==( const Object& ) const;
	bool operator!=( const Object& ) const;

	// 
	// Commands
	// 
public:
	static bool Equals( const Object&, const Object& );
	
	/*
	 * @note Compare two instance. This can be overridden.
	 * @return Return true if both refer to the same object.
	*/
	virtual bool Equals( const Object& rhs ) const;

	/* @note Compare two instance.
	 * @param lhs Left handling side
	 * @param rhs Right handling side
	 * @return Return true if both refer to the same object.
	*/
	static bool ReferenceEquals( const Object& lhs, const Object& rhs );

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


inline bool Object::operator==( const Object& rhs ) const
{
	return this->Equals( rhs );
}

inline bool Object::operator!=( const Object& rhs ) const
{
	return !( *this == rhs );
}

inline bool Object::Equals( const Object& lhs, const Object& rhs )
{
	return lhs.Equals( rhs );
}

inline bool Object::Equals( const Object& rhs ) const
{
	return ( this->GetHashCode( ) == rhs.GetHashCode( ));
}

inline bool Object::ReferenceEquals( const Object& lhs, const Object& rhs )
{
	return ( &lhs == &rhs );
}


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