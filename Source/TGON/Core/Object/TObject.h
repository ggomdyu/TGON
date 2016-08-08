/*
* Author : Cha Junho
* Date : 03/22/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Platform/Config/Build.h"

#include "TType.h"


namespace tgon
{


class TGON_API TObject 
{
/*
	Type definitions
*/
public:
	using Super = void;
	using This = TObject;


/*
	Cons/Destructor
*/
public:
	TObject( );
	
	virtual ~TObject( ) = 0;


/*
	Opeators
*/
	bool operator==( const TObject& ) const;

	bool operator!=( const TObject& ) const;


/*
	Commands
*/
public:
	static bool Equals( const TObject&, const TObject& );
	
	// Compare two instance. This can be overridden.
	virtual bool Equals( const TObject& ) const;

	// Compare two instance. Return true if both refer to the same object.
	static bool ReferenceEquals( const TObject&, const TObject& );


/*
	Gets
*/
	// Return dynamic bound type's hash code.
	virtual uint32_t GetHashCode( ) const = 0;
	
	// Return dynamic bound type's name.
	virtual const char* GetName( ) const = 0;

};


inline bool tgon::TObject::operator==( const TObject& rhs ) const
{
	return this->Equals( rhs );
}

inline bool tgon::TObject::operator!=( const TObject& rhs ) const
{
	return !( *this == rhs );
}

inline bool TObject::Equals( const TObject& lhs, const TObject& rhs )
{
	return lhs.Equals( rhs );
}

inline bool TObject::Equals( const TObject& rhs ) const
{
	return ( this->GetHashCode( ) == rhs.GetHashCode( ));
}

inline bool TObject::ReferenceEquals( const TObject& lhs, const TObject& rhs )
{
	return ( &lhs == &rhs );
}


}


#define TGON_GENERATE_OBJECT_INTERFACE( baseType, superType )\
	using Super = superType;\
	using This = baseType;\
	\
	virtual uint32_t GetHashCode( ) const override\
	{\
		return baseType::GetType( ).GetHashCode( );\
	}\
	virtual const char* GetName( ) const override\
	{\
		return #baseType;\
	}\
	static const tgon::TType& GetType( )\
	{\
		static const tgon::TType ret( #baseType );\
		return ret;\
	}