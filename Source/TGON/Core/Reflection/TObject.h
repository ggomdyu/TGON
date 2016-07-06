/*
* Author : Cha Junho
* Date : 03/22/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Platform/Config/Build.h"
#include "../Math/TMath.h"


namespace tgon
{


class TGON_API TObject 
{
public:
	TObject( );
	
	virtual ~TObject( ) = 0;

	/*
		Commands
	*/
	static bool Equals( const TObject&, const TObject& );
	
	virtual bool Equals( const TObject& ) const;

	// Compare two instance. Return true if both refer to the same object.
	static bool ReferenceEquals( const TObject&, const TObject& );

	/*
		Gets
	*/
	// Return dynam ic binded type's hash code.
	virtual uint32_t GetHashCode( ) const = 0;
	
	// Return dynamic binded type's name.
	virtual const char* ToString( ) const = 0;

	//virtual const TType* GetType( ) const = 0;
};


inline bool TObject::Equals(
	const TObject& lhs,
	const TObject& rhs )
{
	return lhs.Equals( rhs );
}

inline bool TObject::Equals( 
	const TObject& rhs ) const
{
	return ( this->GetHashCode( ) == rhs.GetHashCode( ) );
}

inline bool TObject::ReferenceEquals( 
	const TObject& lhs, 
	const TObject& rhs )
{
	return false;
}


}


#define TGON_OBJECT( myType, parentType )\
	using _ParentTy = parentType;\
	\
	virtual uint32_t GetHashCode( ) const override\
	{\
		static uint32_t hashCode = TMath::GenerateHash( this->ToString( ));\
		return hashCode;\
	}\
	virtual const char* ToString( ) const override\
	{\
		return #myType;\
	}

//\
//	virtual const TType& GetType( ) const\
//	{\
//		static TTypeImpl<myType> typeImpl;\
//		return typeImpl;\
//	}