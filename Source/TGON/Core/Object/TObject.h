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
public:
	/*
		Cons/Destructor
	*/
	TObject( );
	
	virtual ~TObject( ) = 0;

	/*
		Opeators
	*/
	bool operator==( const TObject& ) const;

	bool operator!=( const TObject& ) const;


public:
	/*
		Commands
	*/
	static bool Equals( const TObject&, const TObject& );
	
	// Compare the object paremeter. This can be overridden.
	virtual bool Equals( const TObject& ) const;

	// Compare two instance. Return true if both refer to the same object.
	static bool ReferenceEquals( const TObject&, const TObject& );

	/*
		Gets
	*/
	// Return dynamic binded type's hash code.
	virtual uint32_t GetHashCode( ) const = 0;
	
	// Return dynamic binded type's name.
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

inline bool TObject::Equals(
	const TObject& lhs,
	const TObject& rhs )
{
	return lhs.Equals( rhs );
}

inline bool TObject::Equals( 
	const TObject& rhs ) const
{
	return ( this->GetHashCode( ) == rhs.GetHashCode( ));
}

inline bool TObject::ReferenceEquals( 
	const TObject& lhs, 
	const TObject& rhs )
{
	return ( &lhs == &rhs );
}


}


#define TGON_OBJECT( myType, parentType )\
	using _ParentTy = parentType;\
	\
	virtual uint32_t GetHashCode( ) const override\
	{\
		return myType::GetType( ).GetHashCode( );\
	}\
	virtual const char* GetName( ) const override\
	{\
		return #myType;\
	}\
	static const TType& GetType( )\
	{\
		static const TType ret( #myType );\
		return ret;\
	}